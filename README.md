<h1 align="center">
  <br>
  <img src=".github/logo.png" alt="Geb's Mushrooms" width="500"/>
  <br>
  <a href="https://discord.gg/G8uSGZ8yyf" style="width:250"><img src="https://i.imgur.com/4IyA522.png" alt="Join Our Discord" width="250" style="margin-left:9%"/></a><img src="https://i.imgur.com/3rhti8A.gif" alt="Like & Favorite" width="500" style="margin-left:-10%"/>
  <br>
</h1>

<h3 align="center">Wild Fungi for DayZ</h3>

<p align="center">
  <img alt="Mod Version" src="https://img.shields.io/badge/Mod-v2.0.0-blue?style=for-the-badge">
  <img alt="DayZ Version" src="https://img.shields.io/badge/DayZ-v1.30-teal?style=for-the-badge">
  <a href="https://packjc.github.io/gebsmushrooms/"><img alt="Website" src="https://img.shields.io/badge/Website-Field%20Guide-c25e00?style=for-the-badge"></a>
</p>

<p align="center">
  <a href="https://packjc.github.io/gebsmushrooms/">Website</a> •
  <a href="#key-features">Key Features</a> •
  <a href="#installation">Installation</a> •
  <a href="#main-classnames">Classnames</a> •
  <a href="#credits">Credits</a> •
  <a href="#license">License & Terms</a> •
  <a href='CHANGELOG.md'>Change Log</a>
</p>

## Information

Geb's Mushrooms adds 69 wild fungi to DayZ: 37 edible species, 27 poisonous look-alikes and 5 psychedelic mushrooms, each with its own model and its own baked, boiled, dried, burnt and rotten looks.
They grow on the forest floor near players, through the vanilla events that scatter mushrooms. A field guide to all of them turns up as loot.

## Requirements

* DayZ 1.30. No other mods are needed: load Geb's Mushrooms on both the server and every client.

## Key Features

* **37 edible fungi**: black morel, white morel, lion's mane, giant puffball, chanterelle, chicken of the woods, hen of the woods, shaggy mane, hedgehog mushroom, honey mushroom, wood blewit, lobster mushroom, indigo milk cap, wine cap, velvet foot, beefsteak fungus, cauliflower mushroom, gem-studded puffball, bay bolete, orange birch bolete, old man of the woods, amethyst deceiver, fairy ring champignon, half-free morel, American Caesar, horse mushroom, St George's mushroom, dryad's saddle, bear's head tooth, matsutake, shaggy parasol, witch's butter, turkey tail, hemlock reishi, chaga, crown-tipped coral and cordyceps.
* **27 poisonous look-alikes**: death cap, destroying angel, false morel, jack-o'-lantern, common earthball, sulphur tuft, deadly webcap, green-spored parasol, panther cap, funeral bell, the sickener, yellow stainer, ivory funnel, brown roll-rim, devil's bolete, deadly dapperling, deadly fibrecap, livid pinkgill, false death cap, early false morel, yellow knight, poison pie, clouded agaric, bitter bolete, ringed conecap, stinkhorn and scaly vase chanterelle.
* **5 psychedelic mushrooms**: golden teacher, wavy cap, blue meanie, ovoid and big laughing gym.
* **Real poisons**: poisonous species use DayZ's own illnesses. Most cause food poisoning (charcoal tablets help).
  - The ten deadly ones cause heavy-metal-style organ damage. One whole mushroom is enough to kill, slowly, and only chelation tablets save you; a bite or two only makes you ill.
  - Cooking, drying and rot don't help, except that boiling a false morel leaves only food poisoning.
* **Trips**: the psychedelic mushrooms aren't food. Eating one starts a trip that only the eater sees: the colours drift, the edges of the view darken, and the view breathes, sways and doubles as it swims in waves, drifting out of focus and back. Now and then you laugh at nothing. Very rarely you scream, and the view goes red and wild for a few seconds. A strong one can also turn your stomach on the way up.
  - One whole mushroom lasts from about 20 minutes (big laughing gym) to an hour (blue meanie). More make the trip stronger, then longer. Rotten ones are half as strong, burnt ones a quarter.
  - Logging out pauses a trip, and it carries on when you come back. Dying ends it.
  - Server owners can switch trips off, cap their strength, scale their length or end them at logout (see [Server Settings](#server-settings)).
* **Cook first, boil only**: some edible species, like the morels, must be cooked first. Turkey tail, hemlock reishi and chaga are too tough to eat: boil them fresh for a tea. Dried, they burn in the pot like any dried food.
* **Burnt is not safe**: burnt mushrooms upset the stomach, like vanilla's burnt food.
* **Geb's Mushroom Field Guide**: a field guide to all 69 fungi, grouped by how safe they are to eat, printed on a folded map. Rare loot on the shelves of hunting spots and villages.
* **Like vanilla's mushrooms**: held in vanilla's own hand poses, cooked on a fireplace, and the edible ones work as rabbit-snare bait.
* **Server-controlled by design**: the fungi join the vanilla `Trajectory` events, sorted by habitat. You can add all 69, or only the 37 edible ones, which keeps poisonous and psychedelic fungi out and leaves vanilla's own mushrooms commoner.
* **Ready-made economy files**: on start the server writes the types and both sets of event lines, sorted by habitat, to `$profile:Gebs/mpmissions/`, like Gebsfish. It rewrites them only when the mod's version changes.
* Supported languages:
  - English
  - Czech
  - German
  - Russian
  - Polish
  - Hungarian
  - Italian
  - Spanish
  - French
  - Chinese (Traditional and Simplified)
  - Japanese
  - Portuguese
  > **Note**
  > Although supported languages are listed above, we cannot verify complete accuracy. If you are a native speaker and notice anything wrong, please reach out to us in the Discord via a ticket to assist us in getting proper translations.

## Installation

1. Subscribe to Geb's Mushrooms on the [Steam Workshop](https://steamcommunity.com/sharedfiles/filedetails/?id=3823626210).
2. Install the published `@gebsmushrooms` folder beside the DayZ server executable.
3. Copy the included `.bikey` into the server's `keys` folder.
4. Add `-mod=@gebsmushrooms` to the server launch parameters. Every connecting player must load the same Workshop mod.
5. Start the server once. The mod writes these files to `$profile:Gebs/mpmissions/`:
   - `gebsmushrooms-types.xml` and `gebsmushrooms-cfgeconomycore.xml`: register the types with the `cfgeconomycore.xml` block.
   - `gebsmushrooms-events-children.xml`: all 69 fungi, the poisonous and psychedelic ones included.
   - `gebsmushrooms-events-children-edible.xml`: only the 37 edible fungi.

   Pick one of the two events files and merge its `<child>` lines into the vanilla `Trajectory` events in `db/events.xml`; don't merge both. Every fungus you add takes a share of those events' spawns. All 69 crowd out vanilla's own mushrooms and add 27 poisonous and 5 psychedelic species; the edible-only file adds fewer, so vanilla's mushrooms stay commoner and nothing new is poisonous or psychedelic.

   The files are rewritten only when the mod's version changes or a file is deleted, so keep a copy of any edits.

The [server-owner guide](https://packjc.github.io/gebsmushrooms/#setup) walks through every step, with copy-ready XML.

## Server Settings

On its first start the server also writes `$profile:Gebs/gebsmushrooms.json`. Your edits are never overwritten. Like Gebsfish's configs, every setting has an `...Info` line beside it that explains it, and `ConfigVersion` records the mod version that wrote the file: after an update the mod only stamps the new version and refreshes those help lines. Restart the server after an edit.

| Setting | Default | What it does |
| --- | --- | --- |
| `TripsEnabled` | `1` | `0` switches trips off: the psychedelic mushrooms are then only poor food. |
| `TripStrengthCap` | `1.0` | How strong a trip can get, from `0` to `1` (the full effect). |
| `TripLengthScale` | `1.0` | Every trip's length is multiplied by this, from `0.25` to `3`. |
| `EndTripOnLogout` | `0` | `1` ends a trip when its player logs out. At `0` it pauses and carries on when they come back. |

A paused trip is kept in `$profile:Gebs/trips/`, one small file per player, not in the character save, so removing the mod can't harm characters. A trip left paused for two weeks is dropped.

## Main Classnames

| Category | Classnames |
| --- | --- |
| Edible fungi | `geb_AmericanCaesar`, `geb_AmethystDeceiver`, `geb_BayBolete`, `geb_BearsHeadTooth`, `geb_BeefsteakFungus`, `geb_BlackMorel`, `geb_CauliflowerMushroom`, `geb_Chaga`, `geb_Chanterelle`, `geb_ChickenOfTheWoods`, `geb_Cordyceps`, `geb_CrownTippedCoral`, `geb_DryadsSaddle`, `geb_FairyRingChampignon`, `geb_GemPuffball`, `geb_PuffBall`, `geb_HalfFreeMorel`, `geb_HedgehogMushroom`, `geb_HemlockReishi`, `geb_HenOfTheWoods`, `geb_HoneyMushroom`, `geb_HorseMushroom`, `geb_IndigoMilkCap`, `geb_LionsMane`, `geb_LobsterMushroom`, `geb_Matsutake`, `geb_OldManOfTheWoods`, `geb_OrangeBirchBolete`, `geb_ShaggyMane`, `geb_ShaggyParasol`, `geb_StGeorgesMushroom`, `geb_TurkeyTail`, `geb_VelvetFoot`, `geb_WhiteMorel`, `geb_WineCap`, `geb_WitchsButter`, `geb_WoodBlewit` |
| Poisonous fungi | `geb_BitterBolete`, `geb_BrownRollrim`, `geb_CloudedAgaric`, `geb_Earthball`, `geb_DeadlyDapperling`, `geb_DeadlyFibrecap`, `geb_DeadlyWebcap`, `geb_DeathCap`, `geb_DestroyingAngel`, `geb_DevilsBolete`, `geb_EarlyFalseMorel`, `geb_FalseDeathCap`, `geb_FalseMorel`, `geb_FuneralBell`, `geb_GreenSporedParasol`, `geb_IvoryFunnel`, `geb_JackOLantern`, `geb_LividPinkgill`, `geb_PantherCap`, `geb_PoisonPie`, `geb_ConocybeFilaris`, `geb_ScalyVase`, `geb_Stinkhorn`, `geb_SulphurTuft`, `geb_EmeticRussula`, `geb_YellowKnight`, `geb_YellowStainer` |
| Psychedelic fungi | `geb_BlueMeanie`, `geb_GoldenTeacher`, `geb_LaughingGym`, `geb_Ovoid`, `geb_WavyCap` |
| Field guide | `geb_MushroomGuide` |

The complete searchable list of 70 public config classes is on the [project website](https://packjc.github.io/gebsmushrooms/#classnames).

## The Geb's family

Every mod by Geb stands on its own, so a server can run the ones it wants:

* [Gebsfish](https://github.com/PackJC/gebsfish) ([wiki](https://packjc.github.io/gebsfish/)): the fishing overhaul, with 94 catchable species, rods, lures, coolers, the jon boat and more
* [Geb's Animals](https://github.com/PackJC/gebsanimals) ([website](https://packjc.github.io/gebsanimals/)): 15 wildlife species
* [Geb's Plants](https://github.com/PackJC/gebsplants) ([website](https://packjc.github.io/gebsplants/)): 29 garden crops including wild ginseng
* [Geb's Mushrooms](https://github.com/PackJC/gebsmushrooms) ([website](https://packjc.github.io/gebsmushrooms/)) (this mod): 69 edible, poisonous and psychedelic fungi
* [Alien Invasion](https://github.com/PackJC/alieninvasion) ([website](https://packjc.github.io/alieninvasion/)): UFO crash sites, Little Green Men and the Montauk plasma rifle
* [Thanksgiving](https://steamcommunity.com/sharedfiles/filedetails/?id=2886269800) (Workshop): Pilgrim clothes, turkeys and a flintlock musket for the holiday
* [Great Smoky Mountains](https://github.com/PackJC/greatsmokymountains) ([Workshop](https://steamcommunity.com/sharedfiles/filedetails/?id=2812533524)): a 20 x 20 km map of the Smokies at real scale

Geb's Animals, Plants and Mushrooms used to be one mod, **Geb's Flora & Fauna**. The classnames are unchanged: a server that ran it should load all three to keep every item players already have, because leaving one out deletes its items from the server's storage at the next restart.

## Credits

- Geb, creator and author
- The DayZ community for reporting bugs and inspiration throughout the life of the mod


## Support

If you like this project and think it has improved your server in any way, consider contributing! We are always looking for help with ideas, new models, and any monetary support that can help improve the mod. Open a ticket in the [Discord](https://discord.gg/G8uSGZ8yyf) to discuss how you can contribute, or report a bug on [GitHub](https://github.com/PackJC/gebsmushrooms/issues).


## License

[Attribution-NonCommercial-NoDerivatives 4.0 International](https://github.com/PackJC/gebsmushrooms/blob/master/LICENSE)

## Usage & Terms
This item is NOT authorized (strictly forbidden) for any of these conditions:
- posting on Steam, except under the Steam account Cole.
- hosting on any download server other than Geb's Mushrooms current workshop download.
- hosting on any launcher for distribution other than Geb's Mushrooms current workshop download.
- to be packaged in any form other than Geb's Mushrooms current workshop download.
- to create derivative works.

## PERMISSION IS NOT GRANTED FOR THIS MOD TO BE INCLUDED IN A "SERVER PACK" or "MOD PACK" DO NOT EVEN ASK TO REPACK. NO. NOT ALLOWED.
Use a Collection if you want to include this mod on your server for your users.

## Monetization
You are hereby given monetization approval under the conditions that you follow the DayZ Server Monetization agreement and have obtained permission from Bohemia. Read more here https://www.bohemia.net/monetization

## Donations
We accept donations at https://www.paypal.com/paypalme/packjc every dollar counts and we greatly appreciate any contributions!

### Copyright © Smoky Mountain Software 2022-2026
