#include "AlienPixel.h"
#include <SDL3/SDL.h>
#include <vector>

AlienPixel::AlienPixel() {
    position = {0.0f, 0.0f};
    speed = 100.0f;
}

void AlienPixel::Draw(SDL_Renderer* renderer) {
    for (auto cell : cells) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_FRect alienRect = { position.x + cell.column * 3.0f, position.y + cell.row * 3.0f, 3.0f, 3.0f };
        SDL_RenderFillRect(renderer, &alienRect);
    }
}
