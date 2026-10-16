#include "AssetLoader.h"
#include <SDL3/SDL.h>

std::string AssetLoader::GetAssetPath(const char* relativePath) {
    const char* basePath = SDL_GetBasePath();
    if (basePath == nullptr) {
        return relativePath;
    }

    return std::string(basePath) + relativePath;
}
