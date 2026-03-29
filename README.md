# Knosos Lavirint

A console-based labyrinth game written in C++, inspired by the myth of the Minotaur in the Labyrinth of Knossos.

## About

The player controls a robot navigating a procedurally generated maze. The goal is to reach the exit while avoiding (or defeating) a Minotaur that roams the labyrinth. Along the way, the player can collect magical items that grant temporary abilities.

### Gameplay

- Move the robot using **WASD** keys; press **Q** to quit.
- The maze is generated randomly with a guaranteed path from entrance (`U`) to exit (`I`), verified via flood-fill.
- A Minotaur (`M`) wanders the maze and will chase the robot when adjacent.
- Magical items (`P`) are scattered throughout the maze. Picking one up grants a random effect:
  - **Magla (Fog)** -- reveals only a limited area around the robot for several turns.
  - **Mac (Sword)** -- lets the robot destroy the Minotaur on contact.
  - **Stit (Shield)** -- protects the robot from one Minotaur attack.
  - **Cekic (Hammer)** -- allows the robot to break through a wall once.
- At the end of a session the game state can be saved to a text file.

### Minimum requirements

- Maze dimensions: at least 15x15
- At least 3 magical items

## Usage

```
./knosos <rows> <columns> <items>
```

Example:

```
./knosos 20 25 5
```

## Building

Open `knosos_sv23_2023.sln` in Visual Studio, or compile manually:

```
g++ -o knosos main.cpp Igra.cpp Lavirint.cpp GeneratorLavirinta.cpp Polje.cpp Robot.cpp Minotaur.cpp MagicniPredmeti.cpp Fajl.cpp
```

> **Note:** The project uses `<conio.h>` (`_getch`), so it targets Windows. Porting to Linux/macOS would require replacing `_getch` with a termios-based equivalent.

## Project Structure

| File | Description |
|------|-------------|
| `main.cpp` | Entry point -- parses CLI arguments and starts the game |
| `Igra.cpp/h` | Game loop and core logic (movement, item effects, win/loss conditions) |
| `Lavirint.cpp/h` | Maze data structure, display, and coordinate helpers |
| `GeneratorLavirinta.cpp/h` | Procedural maze generation with flood-fill path validation |
| `Polje.cpp/h` | Single cell in the maze grid |
| `Robot.cpp/h` | Player character with timed effect management |
| `Minotaur.cpp/h` | Minotaur AI (random movement, adjacency detection) |
| `MagicniPredmet.h` / `MagicniPredmeti.cpp` | Item hierarchy and effect application |
| `Fajl.cpp/h` | Save game state to file |
| `data/` | Data files (fog pattern, defense descriptions) |

## Author

Lana Mirkov (sv23-2023)
