# CommonDrops

Written in C++ using SFML.

The current version includes a basic playable survival mode.

## Status

The project currently builds and runs on macOS using CMake and SFML 3.1.0.

Linux and Windows should also be supported through CMake.

## Requirements

- Git
- CMake 3.28 or newer
- A C++17-compatible compiler
- An internet connection during the initial CMake configuration

SFML 3.1.0 and IniPP are downloaded and built automatically by CMake. They do not need to be installed separately.

## Clone

```bash
git clone https://github.com/Drasky-Vanderhoff/CommonDrops.git
cd CommonDrops
```

## Building on macOS

Install the Xcode command-line tools:

```bash
xcode-select --install
```

Install CMake using Homebrew:

```bash
brew install cmake
```

Configure the project:

```bash
cmake -S src -B build -DCMAKE_BUILD_TYPE=Release
```

Build it:

```bash
cmake --build build --parallel
```

Run it:

```bash
cmake -E chdir src ../build/CommonDrops
```

You do not need to install SFML using Homebrew. The required SFML version is downloaded automatically during CMake configuration.

## Building on Linux

Install Git, CMake, a C++17 compiler, and SFML's system dependencies.

On Ubuntu and other Debian-based distributions:

```bash
sudo apt update

sudo apt install \
    build-essential \
    cmake \
    git \
    libxrandr-dev \
    libxcursor-dev \
    libxi-dev \
    libudev-dev \
    libfreetype-dev \
    libflac-dev \
    libvorbis-dev \
    libgl1-mesa-dev \
    libegl1-mesa-dev \
    libharfbuzz-dev \
    libmbedtls-dev \
    libssh2-1-dev
```

Configure the project:

```bash
cmake -S src -B build -DCMAKE_BUILD_TYPE=Release
```

Build it:

```bash
cmake --build build --parallel
```

Run:

```bash
cmake -E chdir src ../build/CommonDrops
```



## Building on Windows

Install:

- Git
- CMake 3.28 or newer
- Visual Studio 2022 with the **Desktop development with C++** workload

Open PowerShell in the repository directory and configure the project:

```powershell
cmake -S src -B build
```

Build a release version:

```powershell
cmake --build build --config Release
```

Run it:

```powershell
cmake -E chdir src ../build/Release/CommonDrops.exe
```

Windows has not yet been tested after the SFML 3.1 migration.

## Working directory

The game currently loads its configuration and assets using paths relative to the `src` directory.

For this reason, run the executable using:

```bash
cmake -E chdir src ../build/CommonDrops
```

Running the executable directly from the repository root may prevent it from finding `commondrops.ini`, graphics, fonts, music, or sound files.

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
