#pragma once
#include <vector>
#include <SDL3/SDL_render.h>
#include "Block.h"

class Obstacle {
public:
    Obstacle(Position position);
    void Draw(SDL_Renderer* renderer);
    Position position;
    std::vector<Block> blocks;
    static std::vector<std::vector<int>> grid;
private:
};
