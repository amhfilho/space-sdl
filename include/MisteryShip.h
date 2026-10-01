#pragma once
#include <SDL3/SDL_render.h>
#include <memory>
#include "Alien.h"
#include "Position.h"

class MisteryShip {
public:
    MisteryShip(SDL_Renderer* renderer);
    void Draw(SDL_Renderer* renderer);

    ~MisteryShip();

    void Deploy();
    void Update(float deltaTime);
private:
    std::unique_ptr<SDL_Texture, TextureDeleter> texture;
    float textureWidth;
    float textureHeight;
    Position position{};
    float speed;
    bool alive;
};
