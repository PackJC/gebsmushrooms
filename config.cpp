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
		overview="Geb's Mushrooms: 63 edible and poisonous fungi for DayZ";	// keep in step with mod.cpp's overview
		action="";
		name="Geb's Mushrooms";
		// Without this the engine looks for gebsmushrooms/Anims/cfg/skeletons.anim.xml
		// and logs "ANIMATION (E): Can't load ..." on every start; point it at vanilla's.
		skeletonDefinitions="DZ/anims/cfg/skeletons.anim.xml";
		credits="DayZ Modding Community";
		author="Geb";
		authorID="0";
		version="1.0.0";
		extra=0;
		type="mod";
		// Config only: no scripts, so no script modules or dependencies.
	};
};
