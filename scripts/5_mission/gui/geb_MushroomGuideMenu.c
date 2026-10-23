// What the player sees while Geb's Mushroom Field Guide is unfolded: no map screen, just the guide held up in the hands with
// the guide printed on its sheet. Vanilla's ActionUnfoldMap opens MENU_MAP, and PlayerBase folds the map away as soon
// as no MENU_MAP is open (unless the server uses the 3D map), so geb_MushroomGuideMission puts this empty menu in the
// map screen's place. It shows nothing (an empty full-screen frame, built here as vanilla's
// GameplayEffectWidgets builds its root, so there's no layout file to pack) and closes on the keys that close
// the map, as MapMenu does; once it has closed, PlayerBase folds the guide away.
class geb_MushroomGuideMenu extends UIScriptedMenu
{
	protected bool m_IsOpening;

	override Widget Init()
	{
		layoutRoot = g_Game.GetWorkspace().CreateWidget(FrameWidgetTypeID, 0, 0, 1.0, 1.0, WidgetFlags.VISIBLE | WidgetFlags.HEXACTPOS | WidgetFlags.VEXACTPOS, 0xffffffff, 0);
		m_IsOpening = true;
		return layoutRoot;
	}

	override void Update(float timeslice)
	{
		super.Update(timeslice);

		// as MapMenu: ignore the frame the menu opened on, then close on the back key, or on the map key when the
		// server lets players open the map without one
		if (!m_IsOpening)
		{
			bool isClosedWithShortcut = CfgGameplayHandler.GetMapIgnoreMapOwnership() && GetUApi().GetInputByID(UAMapToggle).LocalPress();
			if (GetUApi().GetInputByID(UAUIBack).LocalPress() || isClosedWithShortcut)
			{
				CloseGuide();
			}
		}

		m_IsOpening = false;
	}

	// as MapMenu.CloseMapMenu
	protected void CloseGuide()
	{
		PlayerBase player = PlayerBase.Cast(g_Game.GetPlayer());
		if (player)
			player.SetMapClosingSyncSet(false);		// the map is closing: the server is told once

		if (CfgGameplayHandler.GetMapIgnoreMapOwnership())
		{
			if (!CfgGameplayHandler.GetUse3DMap())
			{
				g_Game.GetMission().RemoveActiveInputExcludes({"map"});
			}
			else
			{
				g_Game.GetMission().RemoveActiveInputExcludes({"loopedactions"});
			}

			g_Game.GetMission().RemoveActiveInputRestriction(EInputRestrictors.MAP);
		}

		Close();
	}
};
