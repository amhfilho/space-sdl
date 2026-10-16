//
// Created by Filho, Antonio on 19/09/2026.
//

#include <algorithm>
#include "Ship.h"
#include "Constants.h"

Ship::Ship()
    : position({Constants::Ship::BaseStartX, Constants::Ship::BaseStartY}),
      speed(Constants::Ship::Speed) {

}

void Ship::Draw(SDL_Renderer* renderer, float offsetY) {
    SDL_SetRenderDrawColor(renderer, 47, 230, 23, 255);
    float positionY = Constants::Ship::PositionY;
    shipRect0 = { position.x, positionY, Constants::Ship::BaseWidth, Constants::Ship::BaseHeight };
    shipRect1 = { position.x+2, positionY - Constants::Ship::PartHeight, 46, 5 };
    shipRect2 = { position.x+2 + 23-5, positionY - Constants::Ship::PartHeight * 2, 10, 5 };
    shipRect3 = { position.x+2 + 23-5+3, positionY - Constants::Ship::PartHeight * 3, 4, 5 };
    SDL_RenderFillRect(renderer, &shipRect0);
    SDL_RenderFillRect(renderer, &shipRect1);
    SDL_RenderFillRect(renderer, &shipRect2);
    SDL_RenderFillRect(renderer, &shipRect3);

    for (auto& laser : lasers) {
        laser.Draw(renderer);
    }
}

void Ship::MoveLeft(float deltaTime) {
    float newPosition = position.x - speed * deltaTime;
    if (newPosition < 0) {
        newPosition = 0;
    }
    position.x = newPosition;
}

void Ship::MoveRight(float deltaTime) {
    float newPosition = position.x + speed * deltaTime;
    if (newPosition > Constants::Window::Width - Constants::Ship::BaseWidth) {
        newPosition = Constants::Window::Width - Constants::Ship::BaseWidth;
    }
    position.x = newPosition;
}

void Ship::FireLaser() {
    Laser laser;
    laser.position.x = position.x + Constants::Ship::BaseWidth / 2.0f - Constants::Laser::Width / 2.0f;
    laser.position.y = position.y - Constants::Laser::Height;
    lasers.push_back(laser);
}

void Ship::UpdateLaser(float deltaTime) {
    for (auto& laser : lasers) {
        laser.Update(deltaTime, -1);
    }
    lasers.erase(
        std::remove_if(lasers.begin(), lasers.end(),
                       [](const Laser& laser) { return !laser.active || laser.IsOffScreen(); }),
        lasers.end());
}

std::vector<Laser>& Ship::GetLasers() {
    return lasers;
}

bool Ship::gotHit(const SDL_FRect& laserRect) const {
    const SDL_FRect shipRect = { position.x, position.y, Constants::Ship::BaseWidth, Constants::Ship::BaseHeight };
    return SDL_HasRectIntersectionFloat(&shipRect, &laserRect);
}
