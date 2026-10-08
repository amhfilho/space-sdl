//
// Created by Filho, Antonio on 20/09/2026.
//

#include "Laser.h"
#include "Constants.h"
#include <SDL3/SDL_render.h>
Laser::Laser()
    : position({0, 0}) {
}

void Laser::Draw(SDL_Renderer* renderer) {
    if (active) {
        SDL_SetRenderDrawColor(renderer, 47, 230, 23, 255);
        SDL_FRect shipRect = { position.x, position.y, Constants::Laser::Width, Constants::Laser::Height };
        SDL_RenderFillRect(renderer, &shipRect);
    }
    
}

void Laser::Update(float deltaTime, int direction) {
    position.y += Constants::Laser::Speed * deltaTime * direction;
}

bool Laser::IsOffScreen() const {
    return position.y + Constants::Laser::Height < 0;
}
