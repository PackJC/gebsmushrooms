// The deadly fungi's poison.
// Vanilla digests a food's agents out of the stomach at each agent's digestibility, a tenth for heavy metal, so a
// deadly mushroom that only carried it in its nutrition never came near the lethal phase. Instead, each deadly food
// stage's config says how many heavy-metal agents a gram of it carries ("Food FoodStages <stage> gebHeavyMetalPerGram",
// written by tools/myco/config_myco.py), and eating it puts them straight into the eater, bite by bite, on the server.
// One whole mushroom reaches phase 3 (from 400 agents: steady health loss that only chelation tablets stop); a bite
// or two only makes you ill. Cooking and drying keep the stage's value, as the toxin survives them; a boiled false
// morel has none, and vanilla's mushrooms have none at all.
modded class MushroomBase
{
	// Keep the pool just under its 600 maximum: a count clamped at exactly 600 matches none of the heavy-metal phases.
	protected static const float GEB_HEAVYMETAL_CEILING = 590;

	override void OnConsume(float amount, PlayerBase consumer)
	{
		super.OnConsume(amount, consumer);

		if (!g_Game.IsServer() || !consumer || amount <= 0)
			return;

		float perGram = GebHeavyMetalPerGram();
		if (perGram <= 0)
			return;

		float room = GEB_HEAVYMETAL_CEILING - consumer.GetSingleAgentCount(eAgents.HEAVYMETAL);
		float dose = Math.Min(amount * perGram, room);
		if (dose > 0)
			consumer.InsertAgent(eAgents.HEAVYMETAL, dose);
	}

	// Heavy-metal agents per gram in the current food stage; 0 for the stages (and mushrooms) without any.
	float GebHeavyMetalPerGram()
	{
		FoodStage foodStage = GetFoodStage();
		if (!foodStage)
			return 0;

		string stageName = FoodStage.GetFoodStageName(foodStage.GetFoodStageType());
		string path = "CfgVehicles " + GetType() + " Food FoodStages " + stageName + " gebHeavyMetalPerGram";
		if (!g_Game.ConfigIsExisting(path))
			return 0;

		return g_Game.ConfigGetFloat(path);
	}
};
