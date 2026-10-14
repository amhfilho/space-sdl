#pragma once
#include <vector>
#include <SDL3/SDL_render.h>
#include <unordered_map>
#include "Block.h"
#include "Position.h"
#include "GridPosition.h"
#include "Laser.h"

class Obstacle {
public:
    Obstacle(Position position);
    void Draw(SDL_Renderer* renderer);
    bool CheckCollision(const Laser &laser, int direction);
    Position position;
    std::unordered_map<GridPosition, Block> obstacleBlocks;
    static std::vector<std::vector<int>> grid;
private:
};
