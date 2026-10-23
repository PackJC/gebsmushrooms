// Geb's Mushroom Field Guide (data/config.cpp: geb_MushroomGuide, written by tools/guide/make_guide.py).
// It is vanilla's map (ChernarusMap) retextured: the same model, fold and unfold animations and actions, with the
// guide's cover, sheet and legend. Unfolding it shows that sheet in the hands: with the server's 3D map vanilla
// already does, and with the 2D map scripts/5_mission opens an empty stand-in instead of the map screen.
class geb_MushroomGuide : ChernarusMap
{
	// ItemMap.InitMapState (run from ItemMap's constructor) puts the world's map textures on all three hidden
	// selections; put the guide's own back.
	override void InitMapState()
	{
		super.InitMapState();

		TStringArray textures = GetHiddenSelectionsTextures();
		if (!textures)
			return;

		for (int i = 0; i < textures.Count(); i++)
		{
			SetObjectTexture(i, textures[i]);
		}
	}

	// ItemMap names itself after the world's map; the guide keeps the name and description from its config.
	override bool NameOverride(out string output)
	{
		return false;
	}

	override bool DescriptionOverride(out string output)
	{
		return false;
	}
};
