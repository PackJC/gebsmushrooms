// Geb's Mushrooms' psychedelic fungi. Eating one (on the server, bite by bite) starts a trip, or deepens one already
// going; the server keeps the trip's clock and sends the eater its schedule, and the eater's client shows it
// (geb_TripClient below, the look in scripts/3_game/trip/geb_TripRequester.c).
//
// A whole mushroom gives its kind's strength (config gebTripStrength, 0..1) and, at full strength, its kind's length
// (gebTripMinutes): more mushrooms make it stronger up to full, then longer (to 1.6x). A trip has a come-up of up to
// 5 minutes, a long peak and a slow come-down (the last 35 %). Rotten mushrooms give half, burnt ones a quarter.
// While it's strong the eater laughs now and then (every six minutes or so at the peak), and very rarely (about one
// trip in two) screams: vanilla's heavy-pain yell, which everyone near hears and which flashes the screen red like a
// hit, and then a few seconds of the view going red and wild. A strong come-up can bring the meal back up.
//
// Logging out pauses a trip (the server saves it to $profile:Gebs/trips/<id>.json, not into the character save, so
// removing the mod can't break characters) and it carries on when the player comes back; dying ends it. Server
// owners can switch trips off, cap them, scale their length, or end them on logout (geb_MushroomSettings).

modded class MushroomBase
{
	override void OnConsume(float amount, PlayerBase consumer)
	{
		super.OnConsume(amount, consumer);

		if (!g_Game.IsServer() || !consumer || amount <= 0)
			return;

		string path = "CfgVehicles " + GetType() + " gebTripStrength";
		if (!g_Game.ConfigIsExisting(path))
			return;

		float strength = g_Game.ConfigGetFloat(path);
		float minutes = g_Game.ConfigGetFloat("CfgVehicles " + GetType() + " gebTripMinutes");
		float whole = GetQuantityMax();
		if (whole <= 0)
			whole = 1;

		float potency = 1;
		FoodStage foodStage = GetFoodStage();
		if (foodStage)
		{
			if (foodStage.GetFoodStageType() == FoodStageType.ROTTEN)
				potency = 0.5;
			else if (foodStage.GetFoodStageType() == FoodStageType.BURNED)
				potency = 0.25;
		}

		consumer.GebAddTrip(strength * potency, minutes, amount / whole);
	}
};

// Saved trips: one small JSON file per player while they are offline.
class geb_Trips
{
	static const string FOLDER = "$profile:Gebs/trips";
	static const int STALE_DAYS = 14;			// a trip left this long (the character wiped, say) is dropped

	static string FileOf(string id)
	{
		return FOLDER + "/" + id + ".json";
	}

	// a player id fit for a file name (ids are base64: '/' and '+' would make paths)
	static string SafeId(string id)
	{
		string safe = id;
		safe.Replace("/", "_");
		safe.Replace("+", "-");
		safe.Replace("=", "");
		return safe;
	}

	static int Today()
	{
		int year;
		int month;
		int day;
		GetYearMonthDayUTC(year, month, day);
		return year * 372 + month * 31 + day;
	}

	static void Save(string id, geb_Trip trip)
	{
		if (id == "" || !trip)
			return;

		MakeDirectory("$profile:Gebs");
		MakeDirectory(FOLDER);
		trip.m_SavedDay = Today();
		string error;
		if (!JsonFileLoader<geb_Trip>.SaveFile(FileOf(id), trip, error))
			Print("[GebsMushrooms] Couldn't save a trip: " + error);
	}

	static geb_Trip Load(string id)
	{
		string file = FileOf(id);
		if (id == "" || !FileExist(file))
			return null;

		geb_Trip trip = new geb_Trip();
		string error;
		if (!JsonFileLoader<geb_Trip>.LoadFile(file, trip, error) || !trip || trip.IsOver() || Today() - trip.m_SavedDay > STALE_DAYS)
		{
			DeleteFile(file);
			return null;
		}

		return trip;
	}

	static void Forget(string id)
	{
		if (id != "" && FileExist(FileOf(id)))
			DeleteFile(FileOf(id));
	}
};

modded class PlayerBase
{
	protected ref geb_Trip m_GebTrip;			// server: this player's trip, while there is one
	protected string m_GebTripId;				// server: the player's id, for the trip's file
	protected float m_GebTripSaveTimer;
	protected float m_GebTripLaughTimer = 120;
	protected float m_GebTripScreamTimer = 300;
	protected bool m_GebTripSickChecked;

	static const float GEB_FRIGHT_SECONDS = 4;

	// server: a bite of a psychedelic mushroom. part: how much of a whole one (0..1, more for several bites)
	void GebAddTrip(float strength, float minutes, float part)
	{
		geb_MushroomSettings settings = geb_MushroomSettings.Get();
		if (!settings.TripsEnabled || strength <= 0 || part <= 0 || !IsAlive())
			return;

		if (!m_GebTrip)
		{
			m_GebTrip = new geb_Trip();
			m_GebTripSickChecked = false;
		}

		m_GebTrip.m_Doses = m_GebTrip.m_Doses + part * strength;
		m_GebTrip.m_Minutes = Math.Max(m_GebTrip.m_Minutes, minutes);
		m_GebTrip.m_Strength = Math.Min(settings.TripStrengthCap, m_GebTrip.m_Doses);

		float scale = Math.Clamp(0.4 + 0.6 * m_GebTrip.m_Doses, 0.4, 1.6);
		m_GebTrip.m_Length = Math.Max(m_GebTrip.m_Length, 60 * m_GebTrip.m_Minutes * scale * settings.TripLengthScale);
		m_GebTrip.m_ComeUp = Math.Min(300, 0.12 * m_GebTrip.m_Length);
		m_GebTrip.m_ComeDown = 0.35 * m_GebTrip.m_Length;

		GebSendTrip();
	}

	// server: tell this player's client where its trip is (length 0: none)
	void GebSendTrip()
	{
		PlayerIdentity identity = GetIdentity();
		if (!identity)
			return;

		float elapsed = 0;
		float length = 0;
		float comeUp = 0;
		float comeDown = 0;
		float strength = 0;
		if (m_GebTrip)
		{
			elapsed = m_GebTrip.m_Elapsed;
			length = m_GebTrip.m_Length;
			comeUp = m_GebTrip.m_ComeUp;
			comeDown = m_GebTrip.m_ComeDown;
			strength = m_GebTrip.m_Strength;
		}

		Param5<float, float, float, float, float> data = new Param5<float, float, float, float, float>(elapsed, length, comeUp, comeDown, strength);
		g_Game.RPCSingleParam(this, GEB_RPC_TRIP, data, true, identity);
	}

	// server: the eater's screen goes red and wild for a few seconds
	protected void GebSendFright()
	{
		PlayerIdentity identity = GetIdentity();
		if (!identity)
			return;

		Param1<float> seconds = new Param1<float>(GEB_FRIGHT_SECONDS);
		g_Game.RPCSingleParam(this, GEB_RPC_TRIP_FRIGHT, seconds, true, identity);
	}

	// server, from MissionServer: the player is in the game (a new character or an old one); a trip left paused
	// at logout picks up where it was
	void GebTripConnected(string id)
	{
		m_GebTripId = geb_Trips.SafeId(id);
		if (!m_GebTrip)
			m_GebTrip = geb_Trips.Load(m_GebTripId);

		if (m_GebTrip)
			GebSendTrip();
		m_GebTripSaveTimer = 50;				// and again in 10 s (OnScheduledTick), in case this beat the player to their client
	}

	// server: back within the logout timer, the trip never stopped
	void GebTripReconnected()
	{
		if (m_GebTrip)
			GebSendTrip();
		m_GebTripSaveTimer = 50;
	}

	// server, from MissionServer: the player has left (the logout timer ran out); the trip pauses until they're back
	void GebTripDisconnected()
	{
		if (!m_GebTrip)
			return;

		if (geb_MushroomSettings.Get().EndTripOnLogout)
			geb_Trips.Forget(m_GebTripId);
		else
			geb_Trips.Save(m_GebTripId, m_GebTrip);
		m_GebTrip = null;
	}

	// server, from MissionServer on shutdown: everyone's trip saved as it stands
	void GebTripSaveNow()
	{
		if (m_GebTrip)
			geb_Trips.Save(m_GebTripId, m_GebTrip);
	}

	protected void GebEndTrip()
	{
		m_GebTrip = null;
		geb_Trips.Forget(m_GebTripId);
		GebSendTrip();
	}

	override void OnScheduledTick(float deltaTime)
	{
		super.OnScheduledTick(deltaTime);

		if (!m_GebTrip || !g_Game.IsServer() || !IsAlive())
			return;

		m_GebTrip.m_Elapsed = m_GebTrip.m_Elapsed + deltaTime;
		if (m_GebTrip.IsOver())
		{
			GebEndTrip();
			return;
		}

		float now = m_GebTrip.Intensity(m_GebTrip.m_Elapsed);

		// a fit of laughter now and then while it's strong: a try every 2-4 minutes, half of them at the peak
		m_GebTripLaughTimer -= deltaTime;
		if (m_GebTripLaughTimer <= 0)
		{
			m_GebTripLaughTimer = Math.RandomFloatInclusive(120, 240);
			if (now > 0.45 && Math.RandomFloat01() < now * 0.5 && GetSymptomManager())
				GetSymptomManager().QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_LAUGHTER);
		}

		// very rarely a scare: a try every 4-8 minutes, one in ten at the peak
		m_GebTripScreamTimer -= deltaTime;
		if (m_GebTripScreamTimer <= 0)
		{
			m_GebTripScreamTimer = Math.RandomFloatInclusive(240, 480);
			if (now > 0.6 && !IsUnconscious() && Math.RandomFloat01() < now * 0.1 && GetSymptomManager())
			{
				GetSymptomManager().QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_PAIN_HEAVY);
				GebSendFright();
			}
		}

		// a strong come-up turns the stomach, sometimes
		if (!m_GebTripSickChecked && m_GebTrip.m_Elapsed > m_GebTrip.m_ComeUp * 0.6)
		{
			m_GebTripSickChecked = true;
			if (m_GebTrip.m_Strength >= 0.75 && Math.RandomFloat01() < 0.25 && GetSymptomManager())
				GetSymptomManager().QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_VOMIT);
		}

		// saved now and then too, so a server crash loses little of it, and sent again: a message sent as the player
		// connects can reach their client before the client has their character, and is lost
		m_GebTripSaveTimer += deltaTime;
		if (m_GebTripSaveTimer >= 60)
		{
			m_GebTripSaveTimer = 0;
			geb_Trips.Save(m_GebTripId, m_GebTrip);
			GebSendTrip();
		}
	}

	override void EEKilled(Object killer)
	{
		if (g_Game.IsServer())
		{
			m_GebTrip = null;
			geb_Trips.Forget(m_GebTripId);
		}
		else if (IsControlledPlayer())
		{
			geb_TripClient.Stop();
		}

		super.EEKilled(killer);
	}

	override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx)
	{
		super.OnRPC(sender, rpc_type, ctx);

		if (g_Game.IsDedicatedServer())
			return;

		if (rpc_type == GEB_RPC_TRIP)
		{
			Param5<float, float, float, float, float> data = new Param5<float, float, float, float, float>(0, 0, 0, 0, 0);
			if (ctx.Read(data))
				geb_TripClient.Set(data.param1, data.param2, data.param3, data.param4, data.param5);
		}
		else if (rpc_type == GEB_RPC_TRIP_FRIGHT)
		{
			Param1<float> seconds = new Param1<float>(0);
			if (ctx.Read(seconds))
				geb_TripClient.Fright(seconds.param1);
		}
	}
};

// The eater's client: follows the trip's schedule (its clock runs here too, between the server's messages), eases
// what is shown toward it over a few seconds, and drives the screen effect. Nothing shows while unconscious (the
// trip's time still passes); dying or leaving the game stops it at once.
class geb_TripClient
{
	protected static ref geb_Trip s_Trip;
	protected static float s_Shown;
	protected static float s_FrightLeft;			// seconds of a scare still to come
	protected static float s_FrightLength;
	protected static PPERequester_GebTrip s_Requester;

	// a scare: the view goes red and wild for this long, sharply in and fading out over the last second and a half
	static void Fright(float seconds)
	{
		s_FrightLeft = seconds;
		s_FrightLength = seconds;
	}

	static void Set(float elapsed, float length, float comeUp, float comeDown, float strength)
	{
		if (length <= 0)
		{
			s_Trip = null;
			return;
		}

		if (!s_Trip)
			s_Trip = new geb_Trip();
		s_Trip.m_Elapsed = elapsed;
		s_Trip.m_Length = length;
		s_Trip.m_ComeUp = comeUp;
		s_Trip.m_ComeDown = comeDown;
		s_Trip.m_Strength = strength;
	}

	static void Update(float delta)
	{
		PlayerBase player = PlayerBase.Cast(g_Game.GetPlayer());
		if (!player || !player.IsAlive())
		{
			Stop();
			return;
		}

		float target = 0;
		if (s_Trip)
		{
			s_Trip.m_Elapsed = s_Trip.m_Elapsed + delta;
			if (s_Trip.IsOver())
				s_Trip = null;
			else if (!player.IsUnconscious())
				target = s_Trip.Intensity(s_Trip.m_Elapsed);
		}

		float rate = delta * 0.15;
		s_Shown = s_Shown + Math.Clamp(target - s_Shown, -rate, rate);
		if (s_Shown <= 0.001)
		{
			s_Shown = 0;
			if (s_Requester && s_Requester.IsRequesterRunning())
				s_Requester.Stop();
			return;
		}

		if (!s_Requester)
			Class.CastTo(s_Requester, PPERequesterBank.GetRequester(PPERequester_GebTrip));
		if (!s_Requester)
			return;

		float fright = 0;
		if (s_FrightLeft > 0)
		{
			s_FrightLeft = Math.Max(0, s_FrightLeft - delta);
			float frightIn = Math.Clamp((s_FrightLength - s_FrightLeft) / 0.25, 0, 1);
			float frightOut = Math.Clamp(s_FrightLeft / 1.5, 0, 1);
			fright = frightIn * frightOut;
		}

		if (!s_Requester.IsRequesterRunning())
			s_Requester.Start();
		s_Requester.SetTrip(s_Shown, delta, fright);
	}

	static void Stop()
	{
		s_Trip = null;
		s_Shown = 0;
		s_FrightLeft = 0;
		if (s_Requester && s_Requester.IsRequesterRunning())
			s_Requester.Stop();
	}
};
