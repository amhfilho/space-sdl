# SDL3 Space Invaders

A Space Invaders clone written in C++20 with [Simple DirectMedia Layer - SDL3](https://www.libsdl.org/). This project was inspired by the video
[C++ Space Invaders Tutorial with raylib - Beginner Tutorial (OOP)](https://www.youtube.com/watch?v=TGo3Oxdpr5o&t=5s) 
which uses [raylib](https://www.raylib.com/) instead of SDL3.

## Requirements

- A C++20 compiler (Clang/Apple Clang or GCC)
- CMake 3.28 or newer
- SDL3 libraries:

| Package | Purpose |
|---|---|
| `SDL3` | Window, rendering, input, audio device |
| `SDL3_image` | Loading the PNG sprites in `Graphics/` |
| `SDL3_mixer` | Playing the `.ogg` files in `Sounds/` (SDL3 alone cannot decode Ogg) |

### Install on macOS (Homebrew)

```sh
brew install cmake sdl3 sdl3_image sdl3_mixer
```

The build looks for the libraries in `/opt/homebrew` and `/usr/local`. Refer to 
the [SDL Github page](https://github.com/libsdl-org/SDL/blob/main/INSTALL.md) for instructions on how to install on other 
platforms. The complete documentation can be found 
in [SDL Wiki](https://wiki.libsdl.org/SDL3/FrontPage).

## Build and run

### CMake

```sh
cmake -S . -B build
cmake --build build
./build/space_sdl
```

The build copies `Graphics/` and `Sounds/` next to the executable. Assets are
loaded relative to the executable, so no particular working directory is needed.

### Quick script (macOS)

```sh
./run.sh
```

Compiles all sources with `clang++` into `build/`, copies the assets and starts the game.
Use either `cmake` or `run.sh` for `build/`, not both, since they use different binary names.

## Controls

| Key | Action |
|---|---|
| Space (start screen) | Start the game |
| Left / Right arrows | Move the ship |
| Space | Fire laser (one at a time) |
| Any key (game over) | Restart |
| Esc | Quit |

## Audio

- `Sounds/laser.ogg`: ship fires a laser
- `Sounds/explosion.ogg`: alien, mystery ship or player ship explodes
- `Sounds/music.ogg`: loops on the start and game-over screens

If no audio device is available, the game logs a message and runs silently.

## Project layout

```
src/        C++ sources
include/    Headers
Graphics/   Sprites
Sounds/     Audio files
```
