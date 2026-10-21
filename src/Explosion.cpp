#include <SDL3_image/SDL_image.h>
#include "Explosion.h"
#include "AssetLoader.h"

Explosion::Texture Explosion::LoadTexture(SDL_Renderer* renderer) {
    std::string path = AssetLoader::GetAssetPath("Graphics/explosion.png");

    Texture loaded(IMG_LoadTexture(renderer, path.c_str()));
    if (loaded == nullptr) {
        SDL_Log("Error loading texture: %s", SDL_GetError());
    }

    return loaded;
}

Explosion::Explosion(Position position, SDL_Renderer* renderer, bool persistent)
    : position(position)
    , persistent(persistent)
    , texture(LoadTexture(renderer))
    , textureWidth(0.0f)
    , textureHeight(0.0f)
    , elapsedTime(0.0f)
    , active(true) {

    if (texture != nullptr && !SDL_GetTextureSize(texture.get(), &textureWidth, &textureHeight)) {
        SDL_Log("Error getting texture size: %s", SDL_GetError());
    }
}

void Explosion::Update(float deltaTime) {
    if (!active) {
        return;
    }
    float explosionDuration = 0.3f; // Explosion lasts for 0.3 seconds
    if (persistent) {
        explosionDuration = 1.0f; // Explosion lasts for 1 second
    }
    elapsedTime += deltaTime;
    if (elapsedTime > explosionDuration) {
        active = false;
    }
}

bool Explosion::IsActive() const {
    return active;
}

void Explosion::Draw(SDL_Renderer* renderer) {
    if (texture == nullptr || !active) {
        return;
    }

    SDL_FRect explosionRect = { position.x, position.y, textureWidth, textureHeight };
    SDL_RenderTexture(renderer, texture.get(), nullptr, &explosionRect);
}
