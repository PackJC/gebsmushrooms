class CfgPatches
{
	class gebsmushrooms
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Data",
			"DZ_Scripts",
			"DZ_Gear_Food"
		};
	};
};
class CfgMods
{
	class gebsmushrooms
	{
		dir="gebsmushrooms";
		picture="gebsmushrooms\data\logo.paa";			// picture in expanded description
		logoSmall="gebsmushrooms\data\logo.paa";			// icon next to mod name when description is not expanded
		logo="gebsmushrooms\data\logo.paa";				// logo below game menu
		logoOver="gebsmushrooms\data\logo_hover.paa";	// logo hovered (CfgMods reads logoOver, as mod.cpp does)
		overview="Geb's Mushrooms: 69 edible, poisonous and psychedelic fungi for DayZ";	// keep in step with mod.cpp's overview
		action="";
		name="Geb's Mushrooms";
		// Without this the engine looks for gebsmushrooms/Anims/cfg/skeletons.anim.xml
		// and logs "ANIMATION (E): Can't load ..." on every start; point it at vanilla's.
		skeletonDefinitions="DZ/anims/cfg/skeletons.anim.xml";
		credits="Geb";
		author="Geb";
		authorID="0";
		version="2.0.0";
		extra=0;
		type="mod";
		// Scripts: the Central Economy files written on server start (scripts/3_game, 5_mission), the
		// mushroom field guide's own textures and name, the deadly fungi's poison and the fungi's hand poses
		// (scripts/4_world), and the psychedelic fungi's trips: what one is and the server settings
		// (scripts/3_game/trip), eating and keeping one (4_world/entities/geb_trip.c), and logout and the
		// screen effect each frame (5_mission/mission/geb_TripMission.c).
		dependencies[]=
		{
			"Game",
			"World",
			"Mission"
		};
		class defs
		{
			class gameScriptModule
			{
				value="";
				files[]=
				{
					"gebsmushrooms/scripts/3_game"
				};
			};
			class worldScriptModule
			{
				value="";
				files[]=
				{
					"gebsmushrooms/scripts/4_world"
				};
			};
			class missionScriptModule
			{
				value="";
				files[]=
				{
					"gebsmushrooms/scripts/5_mission"
				};
			};
		};
	};
};
