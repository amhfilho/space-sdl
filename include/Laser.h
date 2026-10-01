#pragma once
#include <SDL3/SDL.h>

#include "Position.h"

class Laser {
public:
    Laser();
    void Draw(SDL_Renderer* renderer);
    void Update(float deltaTime, int direction);
    bool IsOffScreen() const;

    Position position;
    bool active = true;
private:
    float speed;
};
