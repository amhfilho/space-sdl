#include "Obstacle.h"
#include "Constants.h"
#include <algorithm>

std::vector<std::vector<int>> Obstacle::grid = {
        {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
        {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},
    };

Obstacle::Obstacle(Position position) {
    this -> position = position;

    for (int row = 0; row < grid.size(); ++row) {
        for (int col = 0; col < grid[row].size(); ++col) {
            if (grid[row][col] == 1) {
                Position blockPosition = {
                    position.x + static_cast<float>(col) * Constants::Block::Width,
                    position.y + static_cast<float>(row) * Constants::Block::Height
                };
                GridPosition gridPosition = {row, col};
                obstacleBlocks.insert_or_assign(gridPosition, Block(blockPosition));
            }
        }
    }
}

void Obstacle::Draw(SDL_Renderer *renderer) {
    for (auto &block : obstacleBlocks) {
        if (block.second.draw == true) {
            block.second.Draw(renderer);
        }
    }
}

bool Obstacle::CheckCollision(const Laser &laser, int direction) {
    const float laserStartX = laser.position.x;
    const float laserEndX = laserStartX + Constants::Laser::Width;
    // Sweep the whole path travelled this frame so fast lasers can't tunnel through blocks.
    const float sweptStartY = std::min(laser.previousY, laser.position.y);
    const float sweptEndY = std::max(laser.previousY, laser.position.y) + Constants::Laser::Height;

    auto hit = obstacleBlocks.end();
    for (auto it = obstacleBlocks.begin(); it != obstacleBlocks.end(); ++it) {
        const Position blockPosition = it->second.GetPosition();
        const float blockEndX = blockPosition.x + Constants::Block::Width;
        const float blockEndY = blockPosition.y + Constants::Block::Height;

        if (laserStartX < blockEndX && laserEndX > blockPosition.x &&
            sweptStartY < blockEndY && sweptEndY > blockPosition.y) {
            if (hit == obstacleBlocks.end()) {
                hit = it;
                continue;
            }
            // Keep the block the laser reaches first: topmost going down, bottommost going up.
            const float hitY = hit->second.GetPosition().y;
            const float hitX = hit->second.GetPosition().x;
            const bool closer = direction > 0 ? blockPosition.y < hitY : blockPosition.y > hitY;
            if (closer || (blockPosition.y == hitY && blockPosition.x < hitX)) {
                hit = it;
            }
        }
    }

    if (hit == obstacleBlocks.end()) {
        return false;
    }
    // Damage area: the hit block, its left/right neighbours, and the same three blocks in the row above.
    const GridPosition center = hit->first;
    for (int row = center.x - 1; row <= center.x; ++row) {
        for (int col = center.y - 1; col <= center.y + 1; ++col) {
            obstacleBlocks.erase(GridPosition{row, col});
        }
    }
    return true;
}
