//
// Created by Filho, Antonio on 19/09/2026.
//

#include <algorithm>
#include <SDL3_image/SDL_image.h>
#include "Ship.h"
#include "Constants.h"
#include "AssetLoader.h"

SDL_Texture* Ship::texture = nullptr;

Ship::Ship(SDL_Renderer* renderer)
    : speed(Constants::Ship::Speed),
      textureWidth(0.0f),
      textureHeight(0.0f) {

    if (texture == nullptr) {
        std::string path = AssetLoader::GetAssetPath("Graphics/ship.png");
        texture = IMG_LoadTexture(renderer, path.c_str());
        if (texture == nullptr) {
            SDL_Log("Error loading texture: %s", SDL_GetError());
        }
    }

    if (texture != nullptr && !SDL_GetTextureSize(texture, &textureWidth, &textureHeight)) {
        SDL_Log("Error getting texture size: %s", SDL_GetError());
    }

    SetInitialPosition();

    SDL_Log("texture width: %f", textureWidth);
    SDL_Log("texture height: %f", textureHeight);
}

void Ship::SetInitialPosition() {
    position = {Constants::Window::Width/2.0f - textureWidth/2, 655.0f};
}

SDL_Texture* Ship::GetTexture() const {
    return texture;
}

float Ship::GetTextureWidth() const {
    return textureWidth;
}
float Ship::GetTextureHeight() const {
    return textureHeight;
}

void Ship::ClearTexture() {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
}

void Ship::Draw(SDL_Renderer* renderer) {
    if (texture != nullptr) {
        SDL_FRect shipRect = GetRect();
        SDL_RenderTexture(renderer, texture, nullptr, &shipRect);
    }
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
    if (!lasers.empty()) {
        return;
    }
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
    const SDL_FRect shipRect = GetRect();
    return SDL_HasRectIntersectionFloat(&shipRect, &laserRect);
}

SDL_FRect Ship::GetRect() const {
    return {position.x, position.y, textureWidth, textureHeight};
}
