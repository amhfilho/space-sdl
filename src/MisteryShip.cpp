#include "MisteryShip.h"
#include "Random.h"
#include "Constants.h"
#include <SDL3_image/SDL_image.h>

MisteryShip::MisteryShip(SDL_Renderer* renderer)
    : textureWidth(0.0f),
      textureHeight(0.0f),
      position({0.0f, 0.0f}),
      speed(100.0f),
      alive(false) {

    texture.reset(IMG_LoadTexture(renderer, "Graphics/mystery.png"));
    if (texture == nullptr) {
        SDL_Log("Error loading texture: %s", SDL_GetError());
        return;
    }
    if (!SDL_GetTextureSize(texture.get(), &textureWidth, &textureHeight)) {
        SDL_Log("Error getting texture size: %s", SDL_GetError());
    }
}

void MisteryShip::Deploy() {
    alive = true;
    position.y = 10.0f;
    int side = Random::Int(0, 1);
    if (side == 0) {
        position.x = 0.0f;
        speed = 100.0f;
    } else {
        position.x = Constants::Window::Width - textureWidth;
        speed = -100.0f;
    }
}

void MisteryShip::Update(float deltaTime) {
    if (!alive) {
        return;
    }

    position.x += speed * deltaTime;

    if (position.x < -textureWidth || position.x > Constants::Window::Width) {
        alive = false;
    }
}

void MisteryShip::Draw(SDL_Renderer* renderer) {
    if (!alive || texture == nullptr) {
        return;
    }

    SDL_FRect shipRect = { position.x, position.y, textureWidth, textureHeight };
    SDL_RenderTexture(renderer, texture.get(), nullptr, &shipRect);
}

MisteryShip::~MisteryShip() {
    texture.reset();
}
