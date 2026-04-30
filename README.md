# CppRPG

A creature-collecting RPG built in C++ using SFML and SQLite3. Explore a tile-based overworld, encounter wild creatures in tall grass, battle NPC trainers, visit the healing center, and shop for items — all with a classic top-down perspective.

---

## Table of Contents

- [Gameplay Video](#gameplay-video)
- [Features](#features)
- [Project Structure](#project-structure)
- [Dependencies](#dependencies)
- [Building the Project](#building-the-project)
- [Assets](#assets)
  - [Sprites](#sprites)
  - [Maps](#maps)
  - [Fonts](#fonts)
  - [Sounds](#sounds)
- [Database](#database)
  - [Schema Overview](#schema-overview)
  - [Adding Creatures](#adding-creatures)
  - [Adding Moves](#adding-moves)
  - [Adding Presets](#adding-presets)
- [Gameplay](#gameplay)
  - [Controls](#controls)
  - [Map Tiles](#map-tiles)
  - [Battle System](#battle-system)
  - [Items](#items)
- [Extending the Game](#extending-the-game)
  - [Adding a New Tile Type](#adding-a-new-tile-type)
  - [Adding a New Item](#adding-a-new-item)
  - [Adding a New Creature Sprite](#adding-a-new-creature-sprite)
  - [Adding a New Map](#adding-a-new-map)

---

## Gameplay Video

[![Watch the demo](https://img.youtube.com/vi/YOUR_VIDEO_ID/maxresdefault.jpg)](https://www.youtube.com/watch?v=WSYt9E28FJU)

---

## Features

- Tile-based overworld map with scrolling view
- Random wild creature encounters in tall grass
- NPC trainer battles (one-time, defeated trainers disappear)
- Turn-based battle system with physical, special, and effect moves
- Type advantage/disadvantage chart (all 18 types)
- Stat buffs and debuffs
- Item bag: potions, revivals, stat boosters
- In-map shop
- Healing center tile to fully restore your team
- Breakable rock tiles
- SQLite3-driven creature, move, and trainer data

---

## Project Structure

```
CppRPG/
├── assets/
│   ├── fonts/               # Game font(s)
│   ├── maps/                # Map text files
│   ├── sounds/              # Sound effects (WAV)
│   └── sprites/
│       ├── map_sprites/     # Tile and character sprites
│       ├── object_sprites/  # Item sprites
│       ├── pkmn_sprites/    # Creature front/back/mini sprites
│       ├── battleground.png
│       ├── cursor.png
│       ├── dialogbox.png
│       ├── HPbar_green.png
│       ├── HPbar_yellow.png
│       ├── HPbar_red.png
│       ├── menu.png
│       ├── opponentBattleUIbox.png
│       ├── playerBattleUIbox.png
│       └── redCross.png
├── data/
│   └── PkmnRPG.db           # SQLite3 database
├── inc/                     # Header files
└── src/                     # Source files
```

> **Note:** Most assets and the database are not included in the repository (see `.gitignore`). You must supply your own — see the [Assets](#assets) and [Database](#database) sections below.

---

## Dependencies

- **SFML 2.6** — graphics, window, system modules
- **SQLite3** — embedded database for creature/move/trainer data

The project expects shared libraries (`.so`) to be present in a `lib/` directory at the project root, or installed system-wide.

---

## Building the Project

The project is set up for Eclipse CDT (or any Makefile-based build). Object files and binaries are output to `Debug/` or `Release/`.

A typical manual build (adjust include/library paths as needed):

```bash
g++ src/*.cpp \
    -Iinc \
    -Llib \
    -lsfml-graphics -lsfml-window -lsfml-system -lsqlite3 \
    -o CppRPG
```

Run from the project root so that relative asset paths (`./assets/`, `./data/`) resolve correctly:

```bash
./CppRPG
```

---

## Assets

### Sprites

All sprites are loaded relative to `./assets/sprites/`. The filenames below are **hardcoded** and must match exactly (case-sensitive).

#### Battle UI sprites (root of `sprites/`)

| File | Purpose |
|---|---|
| `battleground.png` | Battle background, scaled to 800×600 |
| `playerBattleUIbox.png` | Player's stat box, scaled to 380×120 |
| `opponentBattleUIbox.png` | Opponent's stat box, scaled to 380×100 |
| `HPbar_green.png` | HP bar — full health (>50%) |
| `HPbar_yellow.png` | HP bar — medium health (25–50%) |
| `HPbar_red.png` | HP bar — low health (<25%) |
| `dialogbox.png` | Dialog/text box drawn below the battle screen |
| `cursor.png` | Menu selection cursor, scaled to 50×50 |
| `redCross.png` | Overlaid on KO'd creatures in team select |
| `menu.png` | Full-screen menu background |

#### Map sprites (`sprites/map_sprites/`)

| File | Purpose |
|---|---|
| `grass.png` | Ground tile (walkable, no encounter) |
| `tallGrass.png` | Tall grass tile (encounter on enter) |
| `rock.png` | Wall tile (not walkable, breakable) |
| `brokenRock.png` | Broken wall tile (walkable, shown after breaking) |
| `playerUp/Down/Left/Right.png` | Player character sprites |
| `trainer1.png` | Default NPC trainer sprite |
| `PokeCenter1.png` … `PokeCenter16.png` | Healing center building tiles (4×4 grid = 16 tiles) |

All map sprites are scaled using `SCALE_TILE × TILE_SIZE` (`2.0 × 16 = 32px` on screen).

#### Creature sprites (`sprites/pkmn_sprites/`)

> **Note:** The folder is named `pkmn_sprites/` in the source code and cannot be changed without modifying the display files.

Each creature requires **three** files named after the creature's **exact name as stored in the database**:

```
<Name>_front.png   — opponent's creature in battle
<Name>_back.png    — player's creature in battle
<Name>_mini.png    — small icon shown in team selection
```

For example, for a creature named `Dragon` in the DB:
```
Dragon_front.png
Dragon_back.png
Dragon_mini.png
```

> Names are case-sensitive and must match the `Name` field in the `pokemon` table exactly.

#### Item sprites (`sprites/object_sprites/`)

| File | Item |
|---|---|
| `Potion.png` | Potion |
| `SuperPotion.png` | Super Potion |
| `HyperPotion.png` | Hyper Potion |
| `PotionMax.png` | Max Potion |
| `AttackPlus.png` | Attack+ |
| `DefensePlus.png` | Defense+ |
| `SpAttackPlus.png` | Sp. Attack+ |
| `SpDefensePlus.png` | Sp. Defense+ |
| `SpeedPlus.png` | Speed+ |
| `Rappel.png` | Revive |
| `RappelMax.png` | Max Revive |

### Maps

Maps are plain text files in `assets/maps/`. Each character represents one tile; all rows must have the same length.

| Character | Tile type |
|---|---|
| `.` | Empty (walkable, no grass) |
| `#` | Wall (not walkable, breakable rock) |
| `"` | Tall grass (walkable, random encounter) |
| `T` | Trainer (not walkable until defeated) |
| `1`–`9`, `a`–`g` | Healing center tiles 1–16 (not walkable, heals on interact) |

The map loaded at startup is set in `map.cpp`:
```cpp
std::string map_filename = "./assets/maps/big_map_demo.txt";
```

### Fonts

Place a TrueType font at:
```
assets/fonts/PokemonGb-RAeo.ttf
```
The filename is hardcoded in `main.cpp`. Substitute any `.ttf` font and update the path if needed.

### Sounds

Sound files are present in `assets/sounds/` but are not yet wired into the game logic:
```
boost_sound.wav
hit_damage.wav
selection_beep.wav
```

---

## Database

The game uses a SQLite3 database at `./data/PkmnRPG.db`.

> **Note:** The database filename is hardcoded in `main.cpp` as `PkmnRPG.db`. You may rename it as long as you update that path accordingly.

You must create the database yourself using any SQLite3 tool (e.g. [DB Browser for SQLite](https://sqlitebrowser.org/)).

### Schema Overview

#### `pokemon`

> **Note:** The table is named `pokemon` in the source code and SQL queries; renaming it requires updating the queries in `pkmn.cpp` and `trainer.cpp`.

| Column | Type | Description |
|---|---|---|
| `Id` | INTEGER PK | Creature species ID |
| `Name` | TEXT | Display name (must match sprite filenames) |
| `HP` | INTEGER | Base HP |
| `Attack` | INTEGER | Base Attack |
| `Defense` | INTEGER | Base Defense |
| `Sp_Attack` | INTEGER | Base Sp. Attack |
| `Sp_Defense` | INTEGER | Base Sp. Defense |
| `Speed` | INTEGER | Base Speed |
| `Id_Type1` | INTEGER | Primary type (see `Type` enum) |
| `Id_Type2` | INTEGER | Secondary type (`0` = none) |

#### `move`
| Column | Type | Description |
|---|---|---|
| `Id` | INTEGER PK | Move ID (`0` = empty slot) |
| `Name` | TEXT | Display name |
| `BasePower` | INTEGER | Base damage power |
| `Precision` | INTEGER | Hit chance as integer percentage (e.g. `95` = 95%) |
| `Id_Category` | INTEGER | `1`=Physical, `2`=Special, `3`=Effect |
| `Id_type` | INTEGER | Move type (see `Type` enum) |
| `Stat_Buff` | INTEGER | Buff amount (positive or negative) |
| `Id_Stat` | INTEGER | Stat affected (`0`=none, `1`=Attack, `2`=Defense, etc.) |
| `Buff_Target` | INTEGER | `0`=none, `1`=Self, `2`=Opponent |

#### `pokemon_preset`

A preset is a creature with a specific moveset, used for wild encounters and trainer teams.

| Column | Type | Description |
|---|---|---|
| `Id` | INTEGER PK | Preset ID |
| `Id_Pokemon` | INTEGER FK | References `pokemon.Id` |
| `Id_Move1`–`Id_Move4` | INTEGER FK | References `move.Id` |

The constant `MAX_PKMN_PRESET_ID` in `pkmn.hpp` must be updated to match the highest preset ID in your database.

#### `trainer_preset`
| Column | Type | Description |
|---|---|---|
| `Id` | INTEGER PK | Trainer preset ID |
| `Name` | TEXT | Trainer display name |
| `Id_Pokemon_Preset1`–`Id_Pokemon_Preset6` | INTEGER | References `pokemon_preset.Id` (`0` = empty slot) |
| `Money` | INTEGER | Reward money on defeat |
| `Nbr_MAX_POTION` | INTEGER | Starting Max Potions |
| `Nbr_HYPER_POTION` | INTEGER | Starting Hyper Potions |
| `Nbr_SUPER_POTION` | INTEGER | Starting Super Potions |
| `Nbr_POTION` | INTEGER | Starting Potions |

The constant `MAX_TRAINER_PRESET_ID` in `trainer.hpp` must be updated to match the highest trainer preset ID in your database.

### Type Enum Values

Used in `Id_Type1`, `Id_Type2`, and `Id_type` columns:

```
0=None  1=Normal  2=Fire    3=Water   4=Electric 5=Grass
6=Ice   7=Fighting 8=Poison 9=Ground  10=Flying  11=Psychic
12=Bug  13=Rock   14=Ghost  15=Dragon 16=Dark    17=Steel  18=Fairy
```

### Adding Creatures

1. Insert a row into `pokemon` with a unique `Id` and a `Name` matching your sprite filenames.
2. Create one or more entries in `pokemon_preset` linking the creature to a moveset.
3. Add the three sprite files (`_front`, `_back`, `_mini`) to `assets/sprites/pkmn_sprites/`.
4. Update `MAX_PKMN_PRESET_ID` in `pkmn.hpp` if the new preset ID exceeds the current maximum.

### Adding Moves

Insert a row into `move`. The empty-move slot (Id=0) must always exist. For a pure damage move set `Stat_Buff=0`, `Id_Stat=0`, `Buff_Target=0`.

### Adding Presets

Insert into `pokemon_preset` (for wild encounters or trainer teams) or `trainer_preset` (for NPC trainers). Trainer tiles on the map pick a random trainer preset ID between 1 and `MAX_TRAINER_PRESET_ID`; wild encounters pick a random creature preset ID between 1 and `MAX_PKMN_PRESET_ID`.

---

## Gameplay

### Controls

| Key | Action |
|---|---|
| Arrow keys | Move player |
| `E` | Interact with the tile in front of you |
| `S` | Open the shop |
| `Enter` | Confirm selection in menus |
| `Escape` | Go back / cancel |

### Map Tiles

- **Empty tile** — walk freely, nothing happens.
- **Tall grass** — each step has a 10% chance of triggering a wild battle.
- **Wall (rock)** — blocks movement. Press `E` facing a rock to break it (it becomes walkable).
- **Trainer tile** — press `E` facing a trainer to start a battle. Defeated trainers disappear and their tile becomes walkable.
- **Healing center tiles** — press `E` to fully restore all your creatures' HP.

### Battle System

Battles are turn-based. Each turn you choose one of four actions (labels are hardcoded in French in the source):

- **ATTAQUES** — pick one of your active creature's up to 4 moves.
- **POKÉMONS** — switch your active creature (cannot send out a KO'd one).
- **SAC** — use an item from your bag on a creature.
- **FUIR** — flee.

The faster creature attacks first (tie broken randomly 50/50). If a creature faints mid-turn, the affected side must immediately switch in a replacement.

The AI opponent will:
- Use a potion if its active creature is low on HP (probabilistic).
- Switch to a creature with a better type matchup if one is available (probabilistic, scales with advantage ratio).
- Otherwise pick the highest expected-damage move against your active creature.

Damage formula:
```
damage = 0.2 × BasePower × (Attacker_EffectiveStat / Defender_EffectiveStat) × STAB × TypeBonus
```

STAB (Same Type Attack Bonus) is ×1.5. Stat buffs/debuffs range from −6 to +6 stages.

### Items

| Item | Effect |
|---|---|
| Potion | Restore 20 HP (non-KO only) |
| Super Potion | Restore 60 HP |
| Hyper Potion | Restore 120 HP |
| Max Potion | Fully restore HP |
| Revive | Restore 50% HP to a KO'd creature |
| Max Revive | Fully restore a KO'd creature |
| Attack/Defense/Sp.Atk/Sp.Def/Speed + | +2 stat stages to active creature |

---

## Extending the Game

### Adding a New Tile Type

1. Create `my_tile.hpp` / `my_tile.cpp` inheriting from `Tile`.
2. Implement `onEnter()` and `onInteract()`.
3. Call `setWalkable()`, `setCharToPrint()`, and `setTextureName()` in the constructor.
4. Add a `case` in `Map::createTileFromChar()` in `map.cpp` mapping a character to your new tile.
5. If the tile has a unique sprite, add it to `assets/sprites/map_sprites/` and pre-load it in the `Display_Map` constructor.

### Adding a New Item

1. Add a value to the `Object` enum in `trainer.hpp`.
2. Handle the new item in `Trainer::useObject()` and `Trainer::isObjectUnusable()`.
3. Add its display name to `objectName()` in both `display_fight.cpp` and `display_map.cpp`.
4. Add its price to `objectPrice()` in `display_map.cpp`.
5. Add its sprite filename to `getObjectTexture()` / `getObjectSprite()` in both display files.
6. Place the sprite PNG in `assets/sprites/object_sprites/`.
7. Update `MAX_BAG_SIZE` in the relevant display methods if you now exceed 11 items.

### Adding a New Creature Sprite

Drop three files into `assets/sprites/pkmn_sprites/`:
```
<ExactDatabaseName>_front.png
<ExactDatabaseName>_back.png
<ExactDatabaseName>_mini.png
```
No code changes are needed — sprites are loaded dynamically by name.

### Adding a New Map

1. Create a `.txt` file in `assets/maps/` using the tile characters described above.
2. All rows must be the same length.
3. Update the `map_filename` string in the `Map` constructor (`map.cpp`).
4. Adjust the starting `player_pos` in the `Map` constructor if needed.
