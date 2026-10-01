#pragma once
#include <SDL3/SDL_render.h>
#include "Position.h"
#include <vector>
#include "Laser.h"

class Ship {
public:
    Ship();
    void Draw(SDL_Renderer* renderer, float offsetY);
    void MoveLeft(float deltaTime);
    void MoveRight(float deltaTime);
    void FireLaser();
    void UpdateLaser(float deltaTime);
    std::vector<Laser>& GetLasers();
    bool gotHit(Position& alienLaserPosition);
    Position position;

private:
    float speed;
    std::vector<Laser> lasers;
    SDL_FRect shipRect0;
    SDL_FRect shipRect1;
    SDL_FRect shipRect2;
    SDL_FRect shipRect3;
};
