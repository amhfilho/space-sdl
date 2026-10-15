#pragma once
#include <SDL3/SDL.h>

#include "Position.h"

class Laser {
public:
    Laser();
    void Draw(SDL_Renderer* renderer);
    void Update(float deltaTime, int direction);
    bool IsOffScreen() const;
    SDL_FRect GetRect() const;
    // Area covered since the previous frame, so fast lasers can't tunnel through targets.
    SDL_FRect GetSweptRect() const;

    Position position;
    float previousY = 0.0f;
    bool active = true;
private:
    float speed;
};
