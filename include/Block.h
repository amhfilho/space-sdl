#pragma once
#include <SDL3/SDL_render.h>
#include "Position.h"

class Block {
public:
    Block(Position position);
    void Draw(SDL_Renderer* renderer);
    Position GetPosition() const;
private:
    Position position;
};
