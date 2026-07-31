# CommonDrops

CommonDrops is a free, open-source clone of Magical Drop written in C++ using SFML.

The project was originally created as a learning exercise and because I love Magical Drop. The current version includes a basic playable survival mode.

## Status

The project currently builds and runs on macOS using CMake and SFML 2.6.

Linux and Windows should also be supported through CMake, provided that a compatible SFML 2.x installation is available, but they have not yet been tested after the CMake migration.

## Requirements

- A C++17-compatible compiler
- CMake 3.16 or newer
- SFML 2.5 or 2.6 with these components:
  - Graphics
  - Window
  - System
  - Audio
- Git and an internet connection during the initial CMake configuration

[IniPP](https://github.com/mcmtroffaes/inipp) is downloaded automatically by CMake and does not need to be installed separately.

## Clone

```bash
git clone https://github.com/Drasky-Vanderhoff/CommonDrops.git
cd CommonDrops
```

## Building on macOS

Install the dependencies with Homebrew:

```bash
brew install cmake sfml@2
```

Configure the project:

```bash
cmake \
  -S src \
  -B build \
  -DCMAKE_PREFIX_PATH="$(brew --prefix sfml@2)"
```

Build it:

```bash
cmake --build build --parallel
```

Run it:

```bash
cmake -E chdir src ../build/CommonDrops
```

## Building on Linux or another Unix-like system

Install CMake, a C++17 compiler, and SFML 2.5 or 2.6 using your operating system's package manager.

Configure and build:

```bash
cmake -S src -B build
cmake --build build --parallel
```

Run:

```bash
cmake -E chdir src ../build/CommonDrops
```

When SFML is installed in a non-standard location, provide its installation prefix:

```bash
cmake \
  -S src \
  -B build \
  -DCMAKE_PREFIX_PATH="/path/to/sfml"
```

## Building on Windows

Install:

- CMake
- A C++17-compatible compiler
- SFML 2.5 or 2.6

Configure CMake with the location of SFML:

```powershell
cmake -S src -B build -DCMAKE_PREFIX_PATH="C:/path/to/SFML"
```

Build a release version:

```powershell
cmake --build build --config Release
```

Run the game with `src` as the working directory:

```powershell
cmake -E chdir src ../build/Release/CommonDrops.exe
```

When using a dynamic SFML build, ensure that the required SFML DLL files are either beside the executable or available through `PATH`.

## Controls

| Key | Action |
|---|---|
| Enter | Start or restart the game |
| Left / Right | Move the character |
| X | Grab crystals |
| C | Release crystals |
| Escape | Quit |

## Tools and libraries

- [SFML](https://github.com/SFML/SFML)
- [IniPP](https://github.com/mcmtroffaes/inipp)
- [CMake](https://cmake.org/)

## Roadmap

### Version 0.1

- [x] Implement a basic playable survival mode.

### Version 0.2

- [ ] Make the game configurable, including art, music, sounds, maps, and the crystal matrix.
- [ ] Add unit tests.
- [ ] Make `CrystalMatrix` more reliable in its internal resolution and interactions.

### Possible future features

- Special crystals
- Crystal throwing and grabbing animations
- Challenge mode
- Online play

## Assets

The game assets were obtained from [OpenGameArt](https://opengameart.org/) and were identified as CC0 assets when originally added.

The original asset authors and source pages still need to be documented individually.
