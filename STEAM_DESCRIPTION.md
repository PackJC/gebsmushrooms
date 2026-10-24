[img]https://i.imgur.com/3rhti8A.gif[/img]
[url=https://discord.gg/G8uSGZ8yyf][img]https://i.imgur.com/4IyA522.png[/img][/url]

[h1]Mod Information[/h1]
Geb's Mushrooms adds [b]69 wild fungi[/b] to DayZ: [b]37 edible species[/b], [b]27 poisonous look-alikes[/b] (10 of them deadly) and [b]5 psychedelic mushrooms[/b]. Each one has its own model and its own baked, boiled, dried, burnt and rotten looks, and they grow on the forest floor near players, like vanilla's mushrooms. A field guide to all of them turns up as loot.

It's meant to add immersion and risk, not free food: know which is which before you eat.

[b]Website (every fungus, the setup guide and all the classnames):[/b] [url=https://packjc.github.io/gebsmushrooms/]packjc.github.io/gebsmushrooms[/url]

[h1]Requirements[/h1]
[list]
[*] DayZ 1.30.
[*] No other mods. Load it on both the server and every client.
[/list]

[h1]Features[/h1]
[list]
[*] [b]37 edible fungi:[/b] black and white morels, lion's mane, giant puffball, chanterelle, chicken and hen of the woods, shaggy mane, hedgehog and honey mushrooms, wood blewit, lobster mushroom, indigo milk cap, wine cap, matsutake, chaga, cordyceps and many more.
[*] [b]27 poisonous look-alikes:[/b] death cap, destroying angel, false morel, jack-o'-lantern, panther cap, funeral bell, deadly webcap and more.
[*] [b]5 psychedelic mushrooms:[/b] golden teacher, wavy cap, blue meanie, ovoid and big laughing gym.
[*] [b]Real poisons:[/b] most poisonous species cause food poisoning, eased by charcoal tablets. The ten deadly ones cause organ damage: one whole mushroom is enough to kill, slowly, and only chelation tablets save you. A bite or two only makes you ill. Cooking, drying and rot don't help, except that boiling a false morel leaves only food poisoning.
[*] [b]Trips:[/b] the psychedelic mushrooms aren't food. Eating one starts a trip only you see: the colours drift, the edges of the view darken, and the view breathes, sways and doubles as it swims in waves, drifting out of focus and back. Now and then you laugh at nothing; very rarely you scream and the view goes red and wild for a few seconds. A strong one can turn your stomach on the way up. One whole mushroom lasts from about 20 minutes to an hour; more make it stronger, then longer. Logging out pauses it; dying ends it.
[*] [b]Cook first, boil only:[/b] some edible species, like the morels, upset the stomach raw and have to be cooked. Turkey tail, hemlock reishi and chaga are too tough to eat: boil them fresh for a tea. Dried, they burn in the pot like any dried food.
[*] [b]Burnt isn't safe:[/b] burnt mushrooms upset the stomach, like vanilla's burnt food.
[*] [b]Geb's Mushroom Field Guide:[/b] a field guide to all 69 fungi, grouped by how safe they are to eat, printed on a folded map. Rare loot on the shelves of hunting spots and villages. It opens the way vanilla's map does: as a page on screen on servers with the 2D map (scroll to zoom, drag to move), in your hands on servers with the 3D map.
[*] [b]Like vanilla's mushrooms:[/b] held in vanilla's own hand poses, cooked on a fireplace, and the edible ones work as rabbit-snare bait.
[*] [b]Habitats:[/b] conifer woods, broadleaf woods, and meadows and rich soil, each with its own species.
[*] [b]Server-controlled by design:[/b] the fungi join the vanilla Trajectory events. Add all 69, or only the 37 edible ones to keep poisonous and psychedelic fungi out and leave vanilla's own mushrooms commoner.
[*] [b]Ready-made economy files:[/b] the server writes the types and the event lines, sorted by habitat, like Gebsfish.
[/list]

[h1]Server Setup[/h1]
Start the server once and the mod writes these files to $profile:Gebs/mpmissions/. It rewrites them only when the mod's version changes or a file is deleted, so keep a copy of any edits.
[list]
[*] [b]gebsmushrooms-types.xml[/b] and [b]gebsmushrooms-cfgeconomycore.xml[/b]: copy gebsmushrooms-types.xml into mpmissions/<your mission>/gebsmushrooms/ and paste the block from gebsmushrooms-cfgeconomycore.xml into your cfgeconomycore.xml.
[*] [b]gebsmushrooms-events-children.xml[/b] (all 69 fungi) or [b]gebsmushrooms-events-children-edible.xml[/b] (only the 37 edible ones): pick one and merge its <child> lines into the vanilla [b]Trajectory[/b] events in db/events.xml (TrajectoryConiferous, TrajectoryDeciduous, TrajectoryHumus). They're already sorted by habitat. Don't merge both.
[/list]
Every fungus you add takes a share of those events' spawns. All 69 crowd out vanilla's own mushrooms and add 27 poisonous and 5 psychedelic species. The edible-only file adds fewer, so vanilla's mushrooms stay commoner and nothing new is poisonous or psychedelic. The website has the full guide.

The first start also writes [b]$profile:Gebs/gebsmushrooms.json[/b] (your edits are never overwritten; each setting has an Info line explaining it): TripsEnabled (0 switches trips off), TripStrengthCap (0 to 1), TripLengthScale (0.25 to 3) and EndTripOnLogout (1 ends a trip at logout instead of pausing it).

[h1]Classnames[/h1]
All 70 public classes (the fungi and the field guide) are on the website, with one-click copy and each species' edibility: [url=https://packjc.github.io/gebsmushrooms/#classnames]packjc.github.io/gebsmushrooms/#classnames[/url]

[h1]Coming from Geb's Flora & Fauna[/h1]
Geb's Animals, Plants and Mushrooms used to be one mod, Geb's Flora & Fauna. The classnames haven't changed: if your server ran it, load all three to keep the items players already have. Leaving one out deletes its items from the server's storage at the next restart.

[h1]Supported Languages[/h1]
English, Czech, German, Russian, Polish, Hungarian, Italian, Spanish, French, Chinese (Traditional), Chinese (Simplified), Japanese, Portuguese.

If you're a native speaker and spot a bad translation, please tell us in the Discord.

[h1]The Geb's Family[/h1]
Every mod by Geb stands on its own, so a server can run the ones it wants:
[list]
[*] [url=https://steamcommunity.com/sharedfiles/filedetails/?id=2757509117]Gebsfish[/url]: the fishing overhaul, with 94 catchable species, rods, lures, coolers, the jon boat and more
[*] [url=https://steamcommunity.com/sharedfiles/filedetails/?id=2764114664]Geb's Animals[/url]: 15 wildlife species
[*] [url=https://packjc.github.io/gebsplants/]Geb's Plants[/url]: 30 garden crops including wild ginseng
[*] [b]Geb's Mushrooms[/b] (this mod): 69 edible, poisonous and psychedelic fungi
[*] [url=https://steamcommunity.com/sharedfiles/filedetails/?id=2840597308]Alien Invasion[/url]: UFO crash sites, Little Green Men and the Montauk plasma rifle
[*] [url=https://steamcommunity.com/sharedfiles/filedetails/?id=2886269800]Thanksgiving[/url]: Pilgrim clothes, turkeys and a flintlock musket for the holiday
[*] [url=https://steamcommunity.com/sharedfiles/filedetails/?id=2812533524]Great Smoky Mountains[/url]: a 20 x 20 km map of the Smokies at real scale
[/list]

[h1]Contributors & Credits[/h1]
[list]
[*] Geb, creator and author
[*] The DayZ Modding Community <3
[/list]

[h1]Usage & Terms[/h1]
This item is NOT authorized (strictly forbidden) for any of these conditions:
[list]
[*] posting on Steam, except under the Steam account Cole.
[*] hosting on any download server other than Geb's Mushrooms current workshop download.
[*] hosting on any launcher for distribution other than Geb's Mushrooms current workshop download.
[*] to be packaged in any form other than Geb's Mushrooms current workshop download.
[*] to create derivative works.
[/list]

[h1]PERMISSION IS NOT GRANTED FOR THIS MOD TO BE INCLUDED IN A "SERVER PACK" or "MOD PACK" DO NOT EVEN ASK TO REPACK. NO. NOT ALLOWED.[/h1]
Use a Collection if you want to include this mod on your server for your users.

[h1]Monetization[/h1]
You are hereby given monetization approval under the conditions that you follow the DayZ Server Monetization agreement and have obtained permission from Bohemia. Read more here https://www.bohemia.net/monetization

[h1]Donations[/h1]
We accept donations at https://www.paypal.com/paypalme/packjc. Every dollar counts and we greatly appreciate any contributions!

Copyright © Smoky Mountain Software 2022-2026
