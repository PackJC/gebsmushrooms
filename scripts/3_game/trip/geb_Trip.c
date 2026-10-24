// Geb's Mushrooms' trips: what a trip is (its schedule and how strong it is at any moment), and the settings server
// owners can change in $profile:Gebs/gebsmushrooms.json. The server runs each trip and saves it while its
// player is offline (scripts/4_world/entities/geb_trip.c); the eater's client shows it (geb_TripRequester.c).

const int GEB_RPC_TRIP = 1734697588;		// "gebt": the server sends the eater their trip's schedule
const int GEB_RPC_TRIP_FRIGHT = 1734697589;	// and, very rarely, a scare: a few seconds of the view going red and wild

// One player's trip. Seconds count only while the player is online: a trip pauses when they log out and carries on
// when they come back. Saved to JSON as it is (the fields are its file format).
class geb_Trip
{
	float m_Elapsed;		// seconds into the trip
	float m_Length;			// seconds, from the first bite to sober
	float m_ComeUp;			// seconds to reach the peak
	float m_ComeDown;		// seconds of fading at the end
	float m_Strength;		// 0..1 at the peak
	float m_Doses;			// whole mushrooms eaten, each weighted by its strength
	float m_Minutes;		// the strongest kind eaten so far: its trip length at full strength
	int m_SavedDay;			// the day the file was written (a trip left for weeks is dropped)

	// How strong the trip is at t seconds: up over the come-up, steady through the peak, down over the come-down.
	float Intensity(float t)
	{
		if (t <= 0 || t >= m_Length)
			return 0;

		float up = 1;
		if (m_ComeUp > 0 && t < m_ComeUp)
		{
			float f = t / m_ComeUp;
			up = f * f * (3 - 2 * f);
		}

		float down = 1;
		float fadeStart = m_Length - m_ComeDown;
		if (m_ComeDown > 0 && t > fadeStart)
		{
			float g = 1 - (t - fadeStart) / m_ComeDown;
			down = g * g * (3 - 2 * g);
		}

		return m_Strength * up * down;
	}

	bool IsOver()
	{
		return m_Elapsed >= m_Length;
	}
};

// Server settings, written with these defaults the first time the server starts with the mod. Like Gebsfish's
// configs: ConfigVersion records the mod version that wrote the file, and every setting has an ...Info help text
// beside it. Edits are never overwritten; a new mod version only stamps its version and brings the help texts up to
// date, and the file is written back only when one of those changed.
class geb_MushroomSettings
{
	string ConfigVersionInfo = "The mod version this file was written with. Don't edit it: the mod updates it, and these help texts, when the mod updates. Your settings are never changed.";
	string ConfigVersion = "";
	string TripsEnabledInfo = "1: eating a psychedelic mushroom starts a trip. 0: they do nothing but fill the stomach.";
	int TripsEnabled = 1;
	string TripStrengthCapInfo = "0 to 1: how strong a trip can get. 1 is the full effect; 0.5 caps every trip at half strength.";
	float TripStrengthCap = 1.0;
	string TripLengthScaleInfo = "0.25 to 3: every trip's length is multiplied by this. At 1 one whole mushroom lasts about 20 minutes to an hour.";
	float TripLengthScale = 1.0;
	string EndTripOnLogoutInfo = "0 (default): logging out pauses a trip until the player comes back. 1: logging out ends it.";
	int EndTripOnLogout = 0;

	protected static ref geb_MushroomSettings s_Settings;
	static const string PATH = "$profile:Gebs/gebsmushrooms.json";

	static geb_MushroomSettings Get()
	{
		if (s_Settings)
			return s_Settings;

		geb_MushroomSettings settings = new geb_MushroomSettings();
		string error;
		if (FileExist(PATH))
		{
			if (!JsonFileLoader<geb_MushroomSettings>.LoadFile(PATH, settings, error) || !settings)
			{
				Print("[GebsMushrooms] Couldn't read " + PATH + " (" + error + "), using the defaults (the file is left as it is)");
				settings = new geb_MushroomSettings();
			}
			else if (settings.UpToDate() && g_Game.IsServer())
			{
				JsonFileLoader<geb_MushroomSettings>.SaveFile(PATH, settings, error);
			}
		}
		else if (g_Game.IsServer())
		{
			settings.ConfigVersion = VERSION_GEBSMUSHROOMS;
			MakeDirectory("$profile:Gebs");
			JsonFileLoader<geb_MushroomSettings>.SaveFile(PATH, settings, error);
		}
		s_Settings = settings;

		s_Settings.TripStrengthCap = Math.Clamp(s_Settings.TripStrengthCap, 0, 1);
		s_Settings.TripLengthScale = Math.Clamp(s_Settings.TripLengthScale, 0.25, 3);
		return s_Settings;
	}

	// a file written by another version: stamp this version and bring the help texts up to date (the settings are left
	// alone). Returns true if anything changed, so the file needs writing back.
	bool UpToDate()
	{
		geb_MushroomSettings fresh = new geb_MushroomSettings();
		bool changed = ConfigVersion != VERSION_GEBSMUSHROOMS;
		changed = changed || ConfigVersionInfo != fresh.ConfigVersionInfo || TripsEnabledInfo != fresh.TripsEnabledInfo;
		changed = changed || TripStrengthCapInfo != fresh.TripStrengthCapInfo || TripLengthScaleInfo != fresh.TripLengthScaleInfo;
		changed = changed || EndTripOnLogoutInfo != fresh.EndTripOnLogoutInfo;
		ConfigVersion = VERSION_GEBSMUSHROOMS;
		ConfigVersionInfo = fresh.ConfigVersionInfo;
		TripsEnabledInfo = fresh.TripsEnabledInfo;
		TripStrengthCapInfo = fresh.TripStrengthCapInfo;
		TripLengthScaleInfo = fresh.TripLengthScaleInfo;
		EndTripOnLogoutInfo = fresh.EndTripOnLogoutInfo;
		return changed;
	}
};
