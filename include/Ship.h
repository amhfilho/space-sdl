#pragma once
#include <SDL3/SDL_render.h>
#include "Position.h"
#include <vector>
#include "Laser.h"

class Ship {
public:
    explicit Ship(SDL_Renderer* renderer);

    void SetInitialPosition();

    SDL_Texture *GetTexture() const;

    void Draw(SDL_Renderer* renderer);

    void MoveLeft(float deltaTime);
    void MoveRight(float deltaTime);
    void FireLaser();
    void UpdateLaser(float deltaTime);
    std::vector<Laser>& GetLasers();
    bool gotHit(const SDL_FRect& laserRect) const;
    SDL_FRect GetRect() const;
    Position position;

    // Releases the cached texture. Must be called before the renderer
    // that owns it is destroyed (e.g. in Game's destructor).
    static void ClearTexture();
    float GetTextureWidth() const;
    float GetTextureHeight() const;

private:
    float speed;
    std::vector<Laser> lasers;
    float textureWidth;
    float textureHeight;

    static SDL_Texture* texture; // shared by all Ship instances/draws
};
