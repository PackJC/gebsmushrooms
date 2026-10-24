# Changelog

## 2.0.0

Server owners: on the first start after this update, the server rewrites the economy files in `$profile:Gebs/mpmissions/`: the types and the all-fungi events file gain the five psychedelic species and cordyceps, and the edible-only events file gains cordyceps. Copy any edits you made to them somewhere safe first, then merge the new files as before.

### Added
- **Five psychedelic mushrooms**, a group of their own beside the edible and poisonous fungi: the golden teacher (*Psilocybe cubensis*), the wavy cap (*Psilocybe cyanescens*), the blue meanie (*Panaeolus cyanescens*), the ovoid (*Psilocybe ovoideocystidiata*) and the big laughing gym (*Gymnopilus junonius*). They're in the all-fungi events file and the field guide, but not in the edible-only events file.
- **Trips:** eating a psychedelic mushroom starts a trip that only the eater sees.
  - After a come-up of a few minutes, the colours drift, a violet vignette closes in, and the view breathes, sways and doubles as it swims in waves, with colour fringes at the edges. Every quarter minute or so it drifts out of focus and back. It fades slowly at the end.
  - While it's strong you laugh now and then (every six minutes or so at the peak), and a strong come-up can make you throw up.
  - Very rarely (about one trip in two) you scream: DayZ's heavy-pain yell, which players nearby hear, and a few seconds of the view going blood red, shuddering and doubling.
  - One whole mushroom lasts from about 20 minutes (big laughing gym) to an hour (blue meanie). More make the trip stronger, then longer (up to 1.6 times). Rotten ones are half as strong, burnt ones a quarter.
  - Logging out pauses a trip, and it carries on when the player comes back. A server restart keeps it too. Dying ends it. The server keeps paused trips in `$profile:Gebs/trips/`, not in the character save.
- **Server settings** in `$profile:Gebs/gebsmushrooms.json`, written on the first start and never overwritten: `TripsEnabled`, `TripStrengthCap`, `TripLengthScale` and `EndTripOnLogout` (pause, the default, or end a trip at logout). Like Gebsfish's configs, each setting has an `...Info` line that explains it, and `ConfigVersion` records the mod version that wrote the file (an update only stamps the new version and refreshes the help lines).
- **Cordyceps** (*Cordyceps militaris*, the scarlet caterpillar club): a few bright orange clubs, their heads pimpled with tiny fruiting bodies, rising from the mummified pupa of a moth. It grows on the floor of the broadleaf woods, is edible (simmer it in a soup or a tea), fits a rabbit snare's bait slot like the other edible fungi, and is in the edible-only events file too.

### Changed
- **Geb's Mushroom Field Guide** shows all 69 fungi, and it opens the way vanilla's map does: on servers with the 2D map as a page on the screen (scroll to zoom, drag to move), on servers with the 3D map in your hands.
- **Edible-only spawns:** `gebsmushrooms-events-children-edible.xml` holds the 37 edible fungi and leaves out the psychedelic species as well as the poisonous ones. Merging the all-fungi file instead adds 27 poisonous and 5 psychedelic species.
- **Economy files** are stamped with the mod's version only, like Gebsfish: a restart never rewrites them, only a new version (or a deleted file) does. 1.0.1 also rewrote them when a revision number changed.
- The trip's waves bend further than vanilla's rain-on-the-lens effect allows, so the mod raises that effect's ceiling (a modded `PPEWetDistort`). Rain looks exactly as before.

## 1.0.1

Server owners: on the first start after this update, the server rewrites the economy files in `$profile:Gebs/mpmissions/` (the types now include the Field Guide, and there's a new edible-only events file). Copy any edits you made to them somewhere safe first, then merge the new files as before.

### Added
- **Geb's Mushroom Field Guide**, vanilla's folded map retextured as a field guide: its own cover, and all 63 fungi grouped by how safe they are to eat, with the badges and habitats. Rare loot on the shelves of hunting spots and villages.
- **Edible-only spawns:** the server also writes `gebsmushrooms-events-children-edible.xml`, the event lines for the 36 edible fungi only. Merge it instead of `gebsmushrooms-events-children.xml` (one or the other, not both) to keep the poisonous fungi out of the woods. Merging all 63 adds 27 poisonous species and crowds out vanilla's own mushrooms; the edible-only file adds fewer, so vanilla's stay commoner.
- **Economy files kept up to date:** each file is stamped with the mod's version and a revision, and is rewritten whenever its stamp is out of date, not only when the version changes.
- **Hand poses:** the fungi used to be held like a banana. They now use vanilla's own grips:
  - most are held like the vanilla mushroom they look most like (field mushroom, fly agaric, penny bun, milk cap, horn of plenty, liberty cap or wood ear);
  - the big ones (giant puffball, cauliflower, hen of the woods, lion's mane, bear's head, chicken of the woods, dryad's saddle) are held like a slice of pumpkin;
  - beefsteak fungus and hemlock reishi are held like a steak;
  - the small puffballs, the earthball and chaga are held like a potato.
- **Snare bait:** the 36 edible fungi fit a rabbit snare's bait slot, like vanilla's edible mushrooms.
- **Fireplace cooking:** the fungi now sit on a fireplace's cooking spots the way vanilla's mushrooms do.

### Fixed
- **The deadly fungi now kill.** Their organ-damaging poison went through the stomach at a tenth of its strength, so a whole death cap peaked at about 78 of the 400 agents where the lethal stage begins.
  - Eating one whole deadly mushroom, raw, cooked, dried or rotten, now gives about 530 agents. It causes steady organ damage that kills in about two hours unless you take chelation tablets.
  - A bite or two only makes you ill.
  - A boiled false morel still gives only food poisoning.
  - Their food poisoning stays within vanilla's range; it was up to three times vanilla's strongest.
- **Poisons match their labels.**
  - The Deadly Fibrecap was called deadly but only gave food poisoning; it now carries the organ-damaging poison too, like the death cap.
  - The Bitter Bolete carried no poison at all; it now gives food poisoning, and its description no longer calls it "not poisonous" (in every language).
  - The brown roll-rim, yellow knight and false morel always carried the organ-damaging poison and are now marked deadly on the website, which makes ten deadly species.
- **Raw and poisonous mushrooms make you sick again.** Their sickness was set as toxicity, a value DayZ no longer uses, so these did nothing: the poisonous species, the edible ones meant to be cooked first (the morels, chicken of the woods, wood blewit, wine cap and others), and the tea fungi eaten unboiled. Every one now gives food poisoning, dosed from mild (raw edibles) to strong (the worst poisonous species).
- **Burnt mushrooms upset the stomach**, with the same mild food poisoning as vanilla's burnt food.
- The website marks turkey tail, hemlock reishi and chaga **Boil only**. They're safe only boiled fresh into a tea: raw, baked or dried they upset the stomach, and a dried one burns in the pot, as dried food does in vanilla.
- The indigo milk cap, scaly vase chanterelle and jack-o'-lantern no longer show their gills or ridges through the middle of their funnel-shaped caps.
- The four original mushrooms' text keys have the `geb_` prefix like every other string, so they can't collide with another mod's.
- Lighter models: the eleven busiest mushrooms (cauliflower and hen of the woods, the lion's mane and bear's head, the brackets and the big agarics) drew 5,100 to 8,300 faces up close and in first person. They now draw 3,200 to 4,500, with the same look.
- The mod no longer redefines vanilla's `MushroomBase`, so it can't clash with another mod that changes it.
- **Bumps lit from the right side.** Every mushroom's relief map had up and down swapped, so ridges, scales and pits caught the light from below. All 63 are redone the way DayZ reads them.
- **New models for the cauliflower mushroom, lion's mane and bear's head.** The cauliflower mushroom was a bunch of stalked plates, some stalks floating free of the base; it's now a rounded head of wavy, ruffled lobes that all grow from one hidden base. The lion's mane and bear's head no longer look alike: the lion's mane is a white pom-pom covered in long, hanging spines, and the bear's head is a lumpy clump of short, knobby branches, each hung with a dense tassel of short icicle spines, tier over tier. The bear's head's description now says so too (in every language).
- **A new hen of the woods.** It was a sparse little forest of flat plates on long white sticks; it's now a tall, rounded heap of small, cupped fronds stacked in tiers like shingles, each grey-brown with a cream rim and white underneath, with the short white stalks hidden beneath them.

## 1.0.0

First release as its own mod. Geb's Flora & Fauna is now three mods, so a server can run the parts it wants: [Geb's Animals](https://github.com/PackJC/gebsanimals), [Geb's Plants](https://github.com/PackJC/gebsplants) and **Geb's Mushrooms** (this one). Classnames are unchanged.

Server owners: a server that ran Geb's Flora & Fauna should load all three to keep every item players already have. Leaving one out deletes its items from the server's storage at the next restart.

### Added
- **Ready-made economy files**, like Gebsfish: on start the server writes `gebsmushrooms-types.xml`, `gebsmushrooms-events-children.xml` and `gebsmushrooms-cfgeconomycore.xml` to `$profile:Gebs/mpmissions/`, with the types for all 63 fungi and their event lines, sorted by habitat. They're only rewritten when the mod's version changes (or a file is deleted), so your edits stay put.
- **63 wild fungi** in place of Flora & Fauna's four placeholder mushrooms: 36 edible species and 27 poisonous look-alikes, each with its own model and its own raw, baked, boiled, dried, burnt and rotten looks.
- They grow on the forest floor near players through the vanilla `Trajectory` events that scatter mushrooms, sorted by habitat.
- **Poisons** from DayZ's own illnesses: food poisoning for the poisonous species and organ damage for the deadly ones. Some edible species, like the morels, are meant to be cooked first.
- Every string in all 13 languages: English, Czech, German, Russian, Polish, Hungarian, Italian, Spanish, French, Chinese (Traditional and Simplified), Japanese and Portuguese.
- Mod logo in the same style as Geb's other mods (a toadstool, white in a black frame and orange when hovered), and a website with every species, the server setup and a searchable classname list: [packjc.github.io/gebsmushrooms](https://packjc.github.io/gebsmushrooms/).
