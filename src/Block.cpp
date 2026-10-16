#include "Block.h"

#include "Constants.h"

Block::Block(Position position) {
    this->position = position;
    this->draw = true;
}

void Block::Draw(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 47, 230, 23, 255);
    SDL_FRect blockRect = { position.x, position.y, Constants::Block::Width, Constants::Block::Height };
    SDL_RenderFillRect(renderer, &blockRect);
}

Position Block::GetPosition() const {
    return position;
}
SDL_FRect Block::GetRect() const {
    return { position.x, position.y, Constants::Block::Width, Constants::Block::Height };
}
