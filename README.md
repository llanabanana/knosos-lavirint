# Knosos Lavirint

Console labyrinth game in C++, inspired by the Greek myth of the Minotaur in the Labyrinth of Knossos.
Made as a university project (sv23-2023).

## About the game

You control a robot trying to escape a randomly generated maze. The entrance is at the
top and the exit is at the bottom. Somewhere in the maze, a Minotaur is wandering around --
if it catches you, you lose.

Along the way you can pick up magical items that give you temporary abilities (lasting 3 turns each):

- **Magla (Fog)** -- limits your view to a small area around you
- **Mac (Sword)** -- lets you kill the Minotaur on contact
- **Stit (Shield)** -- blocks one Minotaur attack
- **Cekic (Hammer)** -- lets you break through one wall

The maze is generated procedurally and validated using BFS flood-fill to make sure
there is always a path from entrance to exit. At the end of the game you can save the
maze state to a text file.

## Controls

- **WASD** to move
- **Q** to quit

## How to run

The program takes 3 command-line arguments: rows, columns, and number of items.
Minimum maze size is 15x15 with at least 3 items.

```
./knosos 20 25 5
```

## Building

### Visual Studio

Open `knosos_sv23_2023.sln` and build normally.

### g++ (on Windows)

```
g++ -o knosos main.cpp Igra.cpp Lavirint.cpp GeneratorLavirinta.cpp Polje.cpp Robot.cpp Minotaur.cpp MagicniPredmeti.cpp Fajl.cpp
```

### Windows only

This project uses `<conio.h>` and `_getch()` for keyboard input, so it only
works on Windows. To port it to Linux you would need to replace those with
a termios-based alternative.

## Project structure

| File | What it does |
|------|-------------|
| `main.cpp` | Entry point, parses command-line arguments |
| `Igra.cpp/h` | Game loop, movement logic, win/loss conditions |
| `Lavirint.cpp/h` | Maze data structure and display |
| `GeneratorLavirinta.cpp/h` | Maze generation with flood-fill validation |
| `Polje.cpp/h` | Single cell in the maze |
| `Robot.cpp/h` | Player character with timed effects |
| `Minotaur.cpp/h` | Minotaur movement and adjacency detection |
| `MagicniPredmet.h` / `MagicniPredmeti.cpp` | Magic item classes and effects |
| `Fajl.cpp/h` | Saving game state to file |
| `data/` | Runtime data files used by the game |

## Author

Lana Mirkov
