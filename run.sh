#!/usr/bin/env bash
# Compile all sources in src/ with clang++ and run the game.
set -euo pipefail

cd "$(dirname "$0")"

BUILD_DIR="build"
TARGET="$BUILD_DIR/space_invaders"

# Homebrew prefix: /opt/homebrew (Apple Silicon) or /usr/local (Intel)
PREFIX="$(brew --prefix 2>/dev/null || echo /opt/homebrew)"

if [ ! -d "$PREFIX/include/SDL3" ] || [ ! -d "$PREFIX/include/SDL3_image" ] || [ ! -d "$PREFIX/include/SDL3_mixer" ]; then
    echo "SDL3 / SDL3_image / SDL3_mixer not found in $PREFIX. Install with:" >&2
    echo "  brew install sdl3 sdl3_image sdl3_mixer" >&2
    exit 1
fi

mkdir -p "$BUILD_DIR"

echo "Compiling..."
clang++ -std=c++20 -Wall -Wextra -g \
    -Iinclude -I"$PREFIX/include" \
    src/*.cpp \
    -L"$PREFIX/lib" -Wl,-rpath,"$PREFIX/lib" \
    -lSDL3 -lSDL3_image -lSDL3_mixer \
    -o "$TARGET"

# Assets are resolved relative to the executable (SDL_GetBasePath()).
cp -R Graphics Sounds "$BUILD_DIR/"

echo "Running..."
"./$TARGET"
