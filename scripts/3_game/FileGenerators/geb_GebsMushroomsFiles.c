// Writes Geb's Mushrooms' Central Economy files into $profile:Gebs/mpmissions/ on server start, next to Gebsfish's.
// Each file's second line is "<!-- Version: x -->", the mod version (constants.c). As in Gebsfish, a file is rewritten
// only when it is missing or that version differs, so admin edits survive restarts until the version changes; bump
// VERSION_GEBSMUSHROOMS whenever this generator's output changes.
//
// Server owners copy gebsmushrooms-types.xml into mpmissions/<mission>/gebsmushrooms/ and register it with the block in
// gebsmushrooms-cfgeconomycore.xml. The fungi grow through the vanilla Trajectory events by habitat, so their <child>
// lines are merged into those events by hand: from gebsmushrooms-events-children.xml (all of them) or, for edible
// species only, gebsmushrooms-events-children-edible.xml. The class lists are generated from the species data by
// tools/myco/config_myco.py.
class geb_GebsMushroomsFiles
{
	protected const string DIRECTORY_PATH = "$profile:Gebs/mpmissions/";
	protected const string VERSION_PREFIX = "<!-- Version: ";
	protected const string LOG_PREFIX = "[GebsMushrooms] ";

	void GenerateAll()
	{
		if ( !GetGame() || !GetGame().IsServer() )
			return;

		MakeDirectory("$profile:Gebs");
		MakeDirectory(DIRECTORY_PATH);

		WriteTypes();
		WriteEventChildren();
		WriteEdibleEventChildren();
		WriteEconomyCore();
	}

	// ------------------------------------------------------------------------------------------------------------
	// Files
	// ------------------------------------------------------------------------------------------------------------

	protected void WriteTypes()
	{
		string name = "gebsmushrooms-types.xml";
		FileHandle file = BeginFile(name, "Register with gebsmushrooms-cfgeconomycore.xml, or merge into db/types.xml.");
		if ( !file )
			return;

		FPrintln(file, "<types>");
		FPrintln(file, "    <!-- All 69 fungi (they grow through the vanilla Trajectory events, like vanilla mushrooms) -->");
		WriteTypeList(file, GetFungi(), 0, 900, 0, true, "food", "");
		FPrintln(file, "    <!-- Geb's Mushroom Field Guide: a field guide on vanilla's folded map, rare on the shelves of hunting spots and villages (vanilla's map is 50 in hunting and office spots) -->");
		WriteType(file, "geb_MushroomGuide", 6, 14400, 3, false, "tools", "Hunting,Village", "shelves");
		FPrintln(file, "</types>");

		EndFile(file, name);
	}

	// The <child> lines to add to vanilla events. A mod can't safely redefine a vanilla event from its own events
	// file, so these are merged by hand into db/events.xml.
	protected void WriteEventChildren()
	{
		string name = "gebsmushrooms-events-children.xml";
		FileHandle file = BeginFile(name, "All 69 fungi, the poisonous and psychedelic ones included. Merge each event's <child> lines into the <children> of the vanilla event of the same name in db/events.xml, leaving out any species you don't want. For edible species only, merge gebsmushrooms-events-children-edible.xml instead (use one file, not both).");
		if ( !file )
			return;

		FPrintln(file, "<merge>");
		FPrintln(file, "    <!-- The conifer woods -->");
		FPrintln(file, "    <event name=\"TrajectoryConiferous\">");
		FPrintln(file, "        <children>");
		WriteChildren(file, GetConiferousFungi(), "lootmax=\"0\" lootmin=\"0\" max=\"0\" min=\"0\"");
		FPrintln(file, "        </children>");
		FPrintln(file, "    </event>");
		FPrintln(file, "    <!-- The broadleaf woods -->");
		FPrintln(file, "    <event name=\"TrajectoryDeciduous\">");
		FPrintln(file, "        <children>");
		WriteChildren(file, GetDeciduousFungi(), "lootmax=\"0\" lootmin=\"0\" max=\"0\" min=\"0\"");
		FPrintln(file, "        </children>");
		FPrintln(file, "    </event>");
		FPrintln(file, "    <!-- The meadows and rich soil -->");
		FPrintln(file, "    <event name=\"TrajectoryHumus\">");
		FPrintln(file, "        <children>");
		WriteChildren(file, GetHumusFungi(), "lootmax=\"0\" lootmin=\"0\" max=\"0\" min=\"0\"");
		FPrintln(file, "        </children>");
		FPrintln(file, "    </event>");
		FPrintln(file, "</merge>");

		EndFile(file, name);
	}

	// The same, edible species only: no poisonous or psychedelic fungi join the mushrooms, and vanilla's own stay commoner.
	protected void WriteEdibleEventChildren()
	{
		string name = "gebsmushrooms-events-children-edible.xml";
		FileHandle file = BeginFile(name, "The 37 edible fungi only, in place of gebsmushrooms-events-children.xml (use one file, not both): no poisonous or psychedelic fungi join the vanilla mushrooms, and fewer new species crowd them out. Merge each event's <child> lines into the <children> of the vanilla event of the same name in db/events.xml.");
		if ( !file )
			return;

		FPrintln(file, "<merge>");
		FPrintln(file, "    <!-- The conifer woods -->");
		FPrintln(file, "    <event name=\"TrajectoryConiferous\">");
		FPrintln(file, "        <children>");
		WriteChildren(file, GetConiferousEdibleFungi(), "lootmax=\"0\" lootmin=\"0\" max=\"0\" min=\"0\"");
		FPrintln(file, "        </children>");
		FPrintln(file, "    </event>");
		FPrintln(file, "    <!-- The broadleaf woods -->");
		FPrintln(file, "    <event name=\"TrajectoryDeciduous\">");
		FPrintln(file, "        <children>");
		WriteChildren(file, GetDeciduousEdibleFungi(), "lootmax=\"0\" lootmin=\"0\" max=\"0\" min=\"0\"");
		FPrintln(file, "        </children>");
		FPrintln(file, "    </event>");
		FPrintln(file, "    <!-- The meadows and rich soil -->");
		FPrintln(file, "    <event name=\"TrajectoryHumus\">");
		FPrintln(file, "        <children>");
		WriteChildren(file, GetHumusEdibleFungi(), "lootmax=\"0\" lootmin=\"0\" max=\"0\" min=\"0\"");
		FPrintln(file, "        </children>");
		FPrintln(file, "    </event>");
		FPrintln(file, "</merge>");

		EndFile(file, name);
	}

	// ------------------------------------------------------------------------------------------------------------
	// Class lists
	// ------------------------------------------------------------------------------------------------------------

	// BEGIN class lists: generated by tools/myco/config_myco.py from the species data; edit the generator

	// All fungi
	protected TStringArray GetFungi()
	{
		TStringArray names = {
			"geb_BlackMorel", "geb_WhiteMorel", "geb_LionsMane", "geb_PuffBall",
			"geb_Chanterelle", "geb_ChickenOfTheWoods", "geb_HenOfTheWoods", "geb_ShaggyMane",
			"geb_HedgehogMushroom", "geb_HoneyMushroom", "geb_WoodBlewit", "geb_LobsterMushroom",
			"geb_IndigoMilkCap", "geb_WineCap", "geb_VelvetFoot", "geb_BeefsteakFungus",
			"geb_CauliflowerMushroom", "geb_GemPuffball", "geb_BayBolete", "geb_OrangeBirchBolete",
			"geb_OldManOfTheWoods", "geb_AmethystDeceiver", "geb_FairyRingChampignon", "geb_HalfFreeMorel",
			"geb_DeathCap", "geb_DestroyingAngel", "geb_FalseMorel", "geb_JackOLantern",
			"geb_Earthball", "geb_SulphurTuft", "geb_DeadlyWebcap", "geb_GreenSporedParasol",
			"geb_PantherCap", "geb_FuneralBell", "geb_EmeticRussula", "geb_YellowStainer",
			"geb_IvoryFunnel", "geb_BrownRollrim", "geb_DevilsBolete", "geb_DeadlyDapperling",
			"geb_DeadlyFibrecap", "geb_LividPinkgill", "geb_FalseDeathCap", "geb_EarlyFalseMorel",
			"geb_AmericanCaesar", "geb_HorseMushroom", "geb_StGeorgesMushroom", "geb_DryadsSaddle",
			"geb_BearsHeadTooth", "geb_Matsutake", "geb_ShaggyParasol", "geb_WitchsButter",
			"geb_TurkeyTail", "geb_HemlockReishi", "geb_Chaga", "geb_CrownTippedCoral",
			"geb_Cordyceps", "geb_YellowKnight", "geb_PoisonPie", "geb_CloudedAgaric",
			"geb_BitterBolete", "geb_ConocybeFilaris", "geb_Stinkhorn", "geb_ScalyVase",
			"geb_GoldenTeacher", "geb_WavyCap", "geb_BlueMeanie", "geb_Ovoid",
			"geb_LaughingGym"
		};
		return names;
	}

	// Into TrajectoryConiferous (conifer woods)
	protected TStringArray GetConiferousFungi()
	{
		TStringArray names = {
			"geb_BlackMorel", "geb_Chanterelle", "geb_HedgehogMushroom", "geb_LobsterMushroom",
			"geb_CauliflowerMushroom", "geb_BayBolete", "geb_DestroyingAngel", "geb_FalseMorel",
			"geb_DeadlyWebcap", "geb_PantherCap", "geb_FuneralBell", "geb_EmeticRussula",
			"geb_FalseDeathCap", "geb_Matsutake", "geb_HemlockReishi", "geb_YellowKnight",
			"geb_CloudedAgaric", "geb_BitterBolete", "geb_ScalyVase"
		};
		return names;
	}

	// Into TrajectoryDeciduous (broadleaf woods)
	protected TStringArray GetDeciduousFungi()
	{
		TStringArray names = {
			"geb_WhiteMorel", "geb_LionsMane", "geb_ChickenOfTheWoods", "geb_HenOfTheWoods",
			"geb_HoneyMushroom", "geb_WoodBlewit", "geb_IndigoMilkCap", "geb_VelvetFoot",
			"geb_BeefsteakFungus", "geb_OrangeBirchBolete", "geb_OldManOfTheWoods", "geb_AmethystDeceiver",
			"geb_HalfFreeMorel", "geb_DeathCap", "geb_JackOLantern", "geb_SulphurTuft",
			"geb_BrownRollrim", "geb_DevilsBolete", "geb_DeadlyFibrecap", "geb_LividPinkgill",
			"geb_EarlyFalseMorel", "geb_AmericanCaesar", "geb_DryadsSaddle", "geb_BearsHeadTooth",
			"geb_WitchsButter", "geb_TurkeyTail", "geb_Chaga", "geb_CrownTippedCoral",
			"geb_Cordyceps", "geb_PoisonPie", "geb_Stinkhorn", "geb_WavyCap",
			"geb_Ovoid", "geb_LaughingGym"
		};
		return names;
	}

	// Into TrajectoryHumus (meadows and rich soil)
	protected TStringArray GetHumusFungi()
	{
		TStringArray names = {
			"geb_PuffBall", "geb_ShaggyMane", "geb_WineCap", "geb_GemPuffball",
			"geb_FairyRingChampignon", "geb_Earthball", "geb_GreenSporedParasol", "geb_YellowStainer",
			"geb_IvoryFunnel", "geb_DeadlyDapperling", "geb_HorseMushroom", "geb_StGeorgesMushroom",
			"geb_ShaggyParasol", "geb_ConocybeFilaris", "geb_GoldenTeacher", "geb_BlueMeanie"
		};
		return names;
	}

	// Into TrajectoryConiferous (conifer woods), edible species only
	protected TStringArray GetConiferousEdibleFungi()
	{
		TStringArray names = {
			"geb_BlackMorel", "geb_Chanterelle", "geb_HedgehogMushroom", "geb_LobsterMushroom",
			"geb_CauliflowerMushroom", "geb_BayBolete", "geb_Matsutake", "geb_HemlockReishi"
		};
		return names;
	}

	// Into TrajectoryDeciduous (broadleaf woods), edible species only
	protected TStringArray GetDeciduousEdibleFungi()
	{
		TStringArray names = {
			"geb_WhiteMorel", "geb_LionsMane", "geb_ChickenOfTheWoods", "geb_HenOfTheWoods",
			"geb_HoneyMushroom", "geb_WoodBlewit", "geb_IndigoMilkCap", "geb_VelvetFoot",
			"geb_BeefsteakFungus", "geb_OrangeBirchBolete", "geb_OldManOfTheWoods", "geb_AmethystDeceiver",
			"geb_HalfFreeMorel", "geb_AmericanCaesar", "geb_DryadsSaddle", "geb_BearsHeadTooth",
			"geb_WitchsButter", "geb_TurkeyTail", "geb_Chaga", "geb_CrownTippedCoral",
			"geb_Cordyceps"
		};
		return names;
	}

	// Into TrajectoryHumus (meadows and rich soil), edible species only
	protected TStringArray GetHumusEdibleFungi()
	{
		TStringArray names = {
			"geb_PuffBall", "geb_ShaggyMane", "geb_WineCap", "geb_GemPuffball",
			"geb_FairyRingChampignon", "geb_HorseMushroom", "geb_StGeorgesMushroom", "geb_ShaggyParasol"
		};
		return names;
	}

	// END class lists

	// ------------------------------------------------------------------------------------------------------------
	// Helpers
	// ------------------------------------------------------------------------------------------------------------

	// Opens fileName for writing with the XML/version header. Returns an empty handle when the file is already
	// at the current version (nothing to do) or can't be created.
	protected FileHandle BeginFile(string fileName, string usage)
	{
		FileHandle file;
		string path = DIRECTORY_PATH + fileName;
		if ( IsCurrentVersion(path) )
			return file;

		file = OpenFile(path, FileMode.WRITE);
		if ( !file )
		{
			Print(LOG_PREFIX + "Could not create " + path);
			return file;
		}

		FPrintln(file, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
		FPrintln(file, VERSION_PREFIX + FileStamp() + " -->");
		FPrintln(file, "<!-- Geb's Mushrooms: " + usage + " -->");
		return file;
	}

	protected void EndFile(FileHandle file, string fileName)
	{
		CloseFile(file);
		Print(LOG_PREFIX + fileName + " generated in " + DIRECTORY_PATH);
	}

	protected bool IsCurrentVersion(string path)
	{
		if ( !FileExist(path) )
			return false;

		FileHandle file = OpenFile(path, FileMode.READ);
		if ( !file )
			return false;

		string line;
		string found = "";
		for (int i = 0; i < 5 && FGets(file, line) > 0; i++)
		{
			int start = line.IndexOf(VERSION_PREFIX);
			if ( start == -1 )
				continue;

			string tail = line.Substring(start + VERSION_PREFIX.Length(), line.Length() - start - VERSION_PREFIX.Length());
			int end = tail.IndexOf("-->");
			if ( end != -1 )
				found = tail.Substring(0, end).Trim();
			break;
		}

		CloseFile(file);
		return found == FileStamp();
	}

	// "2.0.0": the mod version
	protected string FileStamp()
	{
		return VERSION_GEBSMUSHROOMS;
	}

	// One <type> per class in the list, all with the same numbers.
	protected void WriteTypeList(FileHandle file, TStringArray classes, int nominal, int lifetime, int min, bool crafted, string category, string usage)
	{
		foreach (string typeName : classes)
			WriteType(file, typeName, nominal, lifetime, min, crafted, category, usage);
	}

	// usage: one usage flag or several separated by commas; placeTag: an optional <tag> (shelves, floor, ground).
	protected void WriteType(FileHandle file, string typeName, int nominal, int lifetime, int min, bool crafted, string category, string usage, string placeTag = "")
	{
		string craftedFlag = "0";
		if ( crafted )
			craftedFlag = "1";

		FPrintln(file, "    <type name=\"" + typeName + "\">");
		FPrintln(file, "        <nominal>" + nominal.ToString() + "</nominal>");
		FPrintln(file, "        <lifetime>" + lifetime.ToString() + "</lifetime>");
		FPrintln(file, "        <restock>0</restock>");
		FPrintln(file, "        <min>" + min.ToString() + "</min>");
		FPrintln(file, "        <quantmin>-1</quantmin>");
		FPrintln(file, "        <quantmax>-1</quantmax>");
		FPrintln(file, "        <cost>100</cost>");
		FPrintln(file, "        <flags count_in_cargo=\"0\" count_in_hoarder=\"0\" count_in_map=\"1\" count_in_player=\"0\" crafted=\"" + craftedFlag + "\" deloot=\"0\"/>");
		if ( category != "" )
			FPrintln(file, "        <category name=\"" + category + "\"/>");
		if ( placeTag != "" )
			FPrintln(file, "        <tag name=\"" + placeTag + "\"/>");
		if ( usage != "" )
		{
			TStringArray usages = new TStringArray;
			usage.Split(",", usages);
			foreach (string usageName : usages)
				FPrintln(file, "        <usage name=\"" + usageName + "\"/>");
		}
		FPrintln(file, "    </type>");
	}

	// <child> lines for one vanilla event: every class in the list with the same attributes.
	protected void WriteChildren(FileHandle file, TStringArray classes, string attributes)
	{
		foreach (string childType : classes)
			FPrintln(file, "            <child " + attributes + " type=\"" + childType + "\"/>");
	}

	protected void WriteEconomyCore()
	{
		string name = "gebsmushrooms-cfgeconomycore.xml";
		FileHandle file = BeginFile(name, "Copy gebsmushrooms-types.xml into mpmissions/<your mission>/gebsmushrooms/ and paste the <ce> block inside <economycore> in cfgeconomycore.xml.");
		if ( !file )
			return;

		FPrintln(file, "<economycore>");
		FPrintln(file, "    <ce folder=\"gebsmushrooms\">");
		FPrintln(file, "        <file name=\"gebsmushrooms-types.xml\" type=\"types\" />");
		FPrintln(file, "    </ce>");
		FPrintln(file, "</economycore>");

		EndFile(file, name);
	}
}
