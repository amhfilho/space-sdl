#pragma once
#include <SDL3/SDL.h>
#include <optional>
#include <vector>

#include "Alien.h"
#include "Explosion.h"
#include "MisteryShip.h"
#include "Obstacle.h"
#include "Ship.h"

class Game {
public:
    // ShipExploding freezes gameplay while the ship's explosion is shown,
    // resuming (via Reset()) as soon as the player presses any key.
    enum class GameState {
        Playing,
        ShipExploding
    };

    Game();
    ~Game();

    bool running;

    bool InitializeWindow();

    void HandleInput();
    void Update();
    void Draw();
private:
    SDL_Window* window;
    SDL_Renderer* renderer;

    Uint64 mTicksCount;
    float deltaTime;
    int shipDirection;
    int alienDirection;
    Uint64 lastLaserShotTime;
    int alienLaserShotInterval;
    Uint64 lastMisteryShipDeployTime;
    int misteryShipDeployInterval;
    bool gameOver;
    GameState state;
    int lifes;

    std::optional<Ship> ship;
    std::vector<Alien> aliens;
    std::vector<Obstacle> obstacles;
    std::vector<Laser> alienLasers;
    std::vector<Explosion> explosions;

    std::optional<MisteryShip> misteryShip;

    void CreateAllAliens();
    void CreateAllObstacles();
    void MoveAliens();
    void MoveAliensDown(int distance);
    void ShootAlienLasers();
    void DeleteInactiveAlienLasers();
    void Reset();
    void CheckLaserCollision();
};
