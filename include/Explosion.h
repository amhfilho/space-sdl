#pragma once
#include <SDL3/SDL_render.h>
#include <memory>
#include "Position.h"

struct ExplosionTextureDeleter {
    void operator()(SDL_Texture* texture) const {
        SDL_DestroyTexture(texture);
    }
};

class Explosion {
public:
    Explosion(Position position, SDL_Renderer* renderer, bool persistent);
    Explosion(const Explosion&) = delete;
    Explosion& operator=(const Explosion&) = delete;
    Explosion(Explosion&&) noexcept = default;
    Explosion& operator=(Explosion&&) noexcept = default;
    void Draw(SDL_Renderer *renderer);
    void Update(float deltaTime);
    bool IsActive() const;
    Position position;
private:
    using Texture = std::unique_ptr<SDL_Texture, ExplosionTextureDeleter>;
    bool persistent;
    Texture texture;
    static Texture LoadTexture(SDL_Renderer* renderer);
    float textureWidth;
    float textureHeight;
    float elapsedTime;
    bool active;
};
