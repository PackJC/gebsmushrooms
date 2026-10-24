// Trips across logouts, reconnects and restarts (server), and the trip's screen effect each frame (client).
// See scripts/4_world/entities/geb_trip.c.
modded class MissionServer
{
	override void OnInit()
	{
		super.OnInit();
		geb_MushroomSettings.Get();				// writes the settings file with its defaults the first time
	}

	// a character in the game, new or loaded: a paused trip resumes
	override void InvokeOnConnect(PlayerBase player, PlayerIdentity identity)
	{
		super.InvokeOnConnect(player, identity);
		if (player && identity)
			player.GebTripConnected(identity.GetId());
	}

	// back before the logout timer ran out: the trip never paused
	override void OnClientReconnectEvent(PlayerIdentity identity, PlayerBase player)
	{
		super.OnClientReconnectEvent(identity, player);
		if (player)
			player.GebTripReconnected();
	}

	// gone for good (the logout timer ran out): the trip is saved, paused (before vanilla handles the body: a
	// character killed on logout then forgets it)
	override void PlayerDisconnected(PlayerBase player, PlayerIdentity identity, string uid)
	{
		if (player)
			player.GebTripDisconnected();
		super.PlayerDisconnected(player, identity, uid);
	}

	// shutting down: every trip saved as it stands
	override void OnMissionFinish()
	{
		array<Man> players = new array<Man>;
		g_Game.GetPlayers(players);
		foreach (Man man : players)
		{
			PlayerBase player = PlayerBase.Cast(man);
			if (player)
				player.GebTripSaveNow();
		}
		super.OnMissionFinish();
	}
};

modded class MissionGameplay
{
	override void OnUpdate(float timeslice)
	{
		super.OnUpdate(timeslice);
		geb_TripClient.Update(timeslice);
	}

	// leaving the server: the effect ends here, so it can't follow the player into the menus
	override void OnMissionFinish()
	{
		geb_TripClient.Stop();
		super.OnMissionFinish();
	}
};
