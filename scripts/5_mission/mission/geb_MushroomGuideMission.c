// Unfolding Geb's Mushroom Field Guide runs vanilla's ActionUnfoldMap, which opens MENU_MAP. While the player holds an
// unfolded guide, that menu is geb_MushroomGuideMenu (the guide as a page, the way the map screen shows the map) instead
// of the map screen; every other map, and the map shortcut key, open as before.
modded class MissionGameplay
{
	override UIScriptedMenu CreateScriptedMenu(int id)
	{
		if (id == MENU_MAP)
		{
			PlayerBase player = PlayerBase.Cast(g_Game.GetPlayer());
			if (player && player.IsMapOpen() && geb_MushroomGuide.Cast(player.GetItemInHands()))
			{
				UIScriptedMenu menu = new geb_MushroomGuideMenu;
				menu.SetID(id);
				return menu;
			}
		}

		return super.CreateScriptedMenu(id);
	}
};
