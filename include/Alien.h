#pragma once
#include <SDL3/SDL_render.h>
#include <memory>
#include <unordered_map>

#include "Position.h"

struct TextureDeleter {
    void operator()(SDL_Texture* texture) const {
        SDL_DestroyTexture(texture);
    }
};

class Alien {
public:
    Alien(Position position, SDL_Renderer* renderer, int type);
    void Draw(SDL_Renderer* renderer);
    void Update(int direction, float deltaTime);

    Position position;
    float GetWidth() const { return textureWidth; }
    float GetHeight() const { return textureHeight; }
    SDL_FRect GetRect() const { return { position.x, position.y, textureWidth, textureHeight }; }

    // Releases all cached textures. Must be called before the renderer
    // that owns them is destroyed (e.g. in Game's destructor).
    static void ClearTextureCache();
private:
    static SDL_Texture* GetOrLoadTexture(SDL_Renderer* renderer, int type);

    static std::unordered_map<int, std::unique_ptr<SDL_Texture, TextureDeleter>> sTextureCache;

    SDL_Texture* texture; // non-owning; owned by sTextureCache
    int type;
    float textureWidth;
    float textureHeight;
};
