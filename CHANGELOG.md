# Changelog

## 1.0.0

First release as its own mod. Geb's Flora & Fauna is now three mods, so a server can run the parts it wants: [Geb's Animals](https://github.com/PackJC/gebsanimals), [Geb's Plants](https://github.com/PackJC/gebsplants) and **Geb's Mushrooms** (this one). Classnames are unchanged.

Server owners: a server that ran Geb's Flora & Fauna should load all three to keep every item players already have. Leaving one out deletes its items from the server's storage at the next restart.

### Added
- **63 wild fungi** in place of Flora & Fauna's four placeholder mushrooms: 36 edible species and 27 poisonous look-alikes, each with its own model and its own raw, baked, boiled, dried, burnt and rotten looks.
- They grow on the forest floor near players through the vanilla `Trajectory` events that scatter mushrooms, sorted by habitat.
- **Real poisons** from DayZ's own illnesses. Most poisonous species cause food poisoning, which charcoal tablets help. The seven deadly ones cause organ damage that cooking doesn't prevent and only chelation tablets stop. Some edible species, like the morels, must be cooked first.
- Every string in all 13 languages: English, Czech, German, Russian, Polish, Hungarian, Italian, Spanish, French, Chinese (Traditional and Simplified), Japanese and Portuguese.
- Mod logo in the same style as Geb's other mods (a toadstool, white in a black frame and orange when hovered), and a website with every species, the server setup and a searchable classname list: [packjc.github.io/gebsmushrooms](https://packjc.github.io/gebsmushrooms/).
