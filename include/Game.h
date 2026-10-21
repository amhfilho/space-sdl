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
    enum class GameState {
        Playing, ShipExploding, DelayAfterExploding, GameOver
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
    Uint64 explosionTime;
    int alienLaserShotInterval;
    Uint64 lastMisteryShipDeployTime;
    int misteryShipDeployInterval;
    bool gameOver;
    GameState state;
    int lifes;
    int score;
    int highScore;

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
    void WriteGameOver();
    void DrawScore();
    void DrawBorder();

    int AddScore(Alien &alien);
};
