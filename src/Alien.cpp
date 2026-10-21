#include <SDL3_image/SDL_image.h>
#include "Alien.h"
#include "AssetLoader.h"

#include <unordered_map>

std::unordered_map<int, std::unique_ptr<SDL_Texture, TextureDeleter>> Alien::sTextureCache;

SDL_Texture* Alien::GetOrLoadTexture(SDL_Renderer* renderer, int type) {
    auto it = sTextureCache.find(type);
    if (it != sTextureCache.end()) {
        return it->second.get();
    }

    const char* relativePath;
    switch (type) {
        case 1: relativePath = "Graphics/alien_1.png"; break;
        case 2: relativePath = "Graphics/alien_2.png"; break;
        case 3: relativePath = "Graphics/alien_3.png"; break;
        default: relativePath = "Graphics/alien_1.png"; break;
    }

    std::string path = AssetLoader::GetAssetPath(relativePath);
    std::unique_ptr<SDL_Texture, TextureDeleter> loaded(IMG_LoadTexture(renderer, path.c_str()));
    if (loaded == nullptr) {
        SDL_Log("Error loading texture: %s", SDL_GetError());
        return nullptr;
    }

    SDL_Texture* raw = loaded.get();
    sTextureCache.emplace(type, std::move(loaded));
    return raw;
}

void Alien::ClearTextureCache() {
    sTextureCache.clear();
}

Alien::Alien(Position position, SDL_Renderer* renderer, int type)
    : position(position),
      texture(GetOrLoadTexture(renderer, type)),
      type(type),
      textureWidth(0.0f),
      textureHeight(0.0f) {

    if (texture != nullptr && !SDL_GetTextureSize(texture, &textureWidth, &textureHeight)) {
        SDL_Log("Error getting texture size: %s", SDL_GetError());
    }
}

void Alien::Update(int direction, float deltaTime) {
    position.x += direction * 55 * deltaTime;
}

void Alien::Draw(SDL_Renderer* renderer) {
    if (texture == nullptr) {
        return;
    }

    SDL_FRect alienRect = { position.x, position.y, textureWidth, textureHeight };
    SDL_RenderTexture(renderer, texture, nullptr, &alienRect);
}

int Alien::GetPointValue() {
    switch (type) {
        case 1: return 10;
        case 2: return 20;
        case 3: return 30;
        default: return 10;
    }
}
