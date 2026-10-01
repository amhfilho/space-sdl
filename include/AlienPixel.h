#pragma once
#include <SDL3/SDL_render.h>
#include <vector>
#include "Position.h"

struct Cell { int row; int column; };
class AlienPixel {
public:
    AlienPixel();
    std::vector<Cell> cells;
    void Draw(SDL_Renderer* renderer);
private:
    Position position;
    float speed;
};
