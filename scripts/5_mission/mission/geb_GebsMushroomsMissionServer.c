modded class MissionServer
{
	override void OnInit()
	{
		super.OnInit();

		// Economy files for server owners, written to $profile:Gebs/mpmissions/ (skipped when already current)
		geb_GebsMushroomsFiles files = new geb_GebsMushroomsFiles();
		files.GenerateAll();
	}
};
