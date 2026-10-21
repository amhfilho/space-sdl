#include "Game.h"

#include "Constants.h"
#include "MisteryShip.h"
#include "Explosion.h"
#include "Random.h"

Game::Game()
    : running(true)
    , renderer(nullptr)
    , shipDirection(0)
    , alienDirection(1)
    , lastLaserShotTime(0)
    , explosionTime(0)
    , alienLaserShotInterval(500)
    , lastMisteryShipDeployTime(0)
    , misteryShipDeployInterval(Random::Int(10000, 20000)) // Deploy every 10 to 20 seconds
    , gameOver(false)
    , state(GameState::Playing)
    , lifes(3)
{

    mTicksCount = SDL_GetTicks();
    deltaTime = 0.0f;

    CreateAllObstacles();
}

bool Game::InitializeWindow() {
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        SDL_Log("Error starting SDL3: %s", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow(Constants::Window::Title, Constants::Window::Width, Constants::Window::Height, 0);
    if (!window) {
        SDL_Log("Error creating window: %s", SDL_GetError());
        SDL_Quit();
        return false;
    }

    renderer = SDL_CreateRenderer(window, nullptr);
    if (!renderer) {
        SDL_Log("Error creating renderer: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }

    if (!SDL_SetRenderVSync(renderer, 1))
    {
        SDL_Log("Unable to enable vertical sync: %s", SDL_GetError());
        return false;
    }

    ship.emplace(renderer);
    CreateAllAliens();
    misteryShip.emplace(renderer);

    return true;
}

void Game::HandleInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_EVENT_QUIT:
                running = false;
                break;
            case SDL_EVENT_KEY_DOWN:
                switch (event.key.key) {
                    case SDLK_ESCAPE:
                        running = false;
                        break;
                }
                if (state == GameState::GameOver) {
                    Reset();
                }
                else if (event.key.key == SDLK_SPACE && !event.key.repeat) {
                    ship->FireLaser();
                }
                break;
        }

        if (state == GameState::GameOver) {
            shipDirection = 0;
            continue;
        }

        const bool* keys = SDL_GetKeyboardState(nullptr);
        if (keys[SDL_SCANCODE_LEFT]) {
            shipDirection = -1;
        }
        else if (keys[SDL_SCANCODE_RIGHT]) {
            shipDirection = 1;
        }
        else {
            shipDirection = 0;
        }
    }
}

void Game::Update() {
    Uint64 currentTicks = SDL_GetTicks();
    deltaTime = (currentTicks - mTicksCount) / 1000.0f;
    mTicksCount = currentTicks;

    for (auto& explosion : explosions) {
        explosion.Update(deltaTime);
    }
    explosions.erase(
        std::remove_if(explosions.begin(), explosions.end(),
                       [](const Explosion& explosion) { return !explosion.IsActive(); }),
        explosions.end());


    if (state == GameState::ShipExploding) {
        if (explosions.empty()) {
            // The persistent explosion has run its course: lose a life and
            // start the 1-second delay before a new ship appears.
            lifes--;
            if (lifes == 0) {
                state = GameState::GameOver;
            } else {
                explosionTime = currentTicks;
                state = GameState::DelayAfterExploding;
            }
        } else {
            // Gameplay is frozen while the ship's explosion plays out.
            return;
        }
    }
    Uint64 delayAfterExploding = 1000;
    if (state == GameState::DelayAfterExploding) {
        if (currentTicks - explosionTime > delayAfterExploding) {
            // Spawn a new ship and resume play.
            ship->SetInitialPosition();
            ship->GetLasers().clear();
            state = GameState::Playing;
        }
        else {
            return;
        }
    }

    if (state == GameState::GameOver) {
        return;
    }

    if (shipDirection == -1) {
        ship->MoveLeft(deltaTime);
    } else if (shipDirection == 1) {
        ship->MoveRight(deltaTime);
    }

    ship->UpdateLaser(deltaTime);

    MoveAliens();

    if (currentTicks - lastLaserShotTime > alienLaserShotInterval) {
        ShootAlienLasers();
        lastLaserShotTime = currentTicks;
    }

    for (auto& laser : alienLasers) {
        laser.Update(deltaTime, 1);
    }

    DeleteInactiveAlienLasers();

    if (currentTicks - lastMisteryShipDeployTime > misteryShipDeployInterval) {
        misteryShip->Deploy();
        lastMisteryShipDeployTime = currentTicks;
        misteryShipDeployInterval = Random::Int(10000, 20000); // Deploy every 10 to 20 seconds
    }

    misteryShip->Update(deltaTime);

    CheckLaserCollision();
}

void Game::Draw() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    if (state == GameState::GameOver) {
        WriteGameOver();
    }

    if (state == GameState::Playing) {
        ship->Draw(renderer);
    }

    float init = 10.0f;
    for (int i = 0; i < lifes; i++) {
        float offsetX = ship->GetTextureWidth()*i + (10.0f*i) + init;
        SDL_Texture *texture = ship->GetTexture();
        SDL_FRect shipRect = { offsetX, 775.0f, ship->GetTextureWidth(), ship->GetTextureHeight() };
        SDL_RenderTexture(renderer, texture, nullptr, &shipRect);
    }
    for (auto& alien : aliens) {
        alien.Draw(renderer);
    }
    for (auto& obstacle : obstacles) {
        obstacle.Draw(renderer);
    }
    for (auto& laser : alienLasers) {
        laser.Draw(renderer);
    }

    misteryShip->Draw(renderer);

    for (auto& explosion : explosions) {
        explosion.Draw(renderer);
    }

    SDL_RenderLine(renderer,
        0 ,
        Constants::Space::Height,
        Constants::Window::Width,
        Constants::Space::Height);

    SDL_RenderPresent(renderer);
}

Game::~Game() {
    aliens.clear();
    Alien::ClearTextureCache();
    Ship::ClearTexture();
    misteryShip.reset();
    explosions.clear();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::CreateAllObstacles() {
    obstacles.clear();
    int obstacleWidth = Obstacle::grid[0].size() * Constants::Block::Width;
    float gap = (Constants::Window::Width - (4 * obstacleWidth)) / 5; // Calculate the gap between obstacles

    for (int i = 0; i < 4; ++i) {
        float offsetX = (i + 1) * gap + i * obstacleWidth;

        Position position = { offsetX, Constants::Obstacle::Y };
        obstacles.emplace_back(position);
    }
}

void Game::CreateAllAliens() {
    aliens.clear();
    float totalWidth = 11 * 55; // 11 aliens, each 55 pixels apart
    float offsetX = (Constants::Window::Width - totalWidth) / 2;
    float offsetY = 110.0f;

    for (int row = 0; row < 5; row++) {
        for (int col = 0; col < 11; col++) {
            float x = col * 55 + offsetX;
            float y = row * 55 + offsetY;
            int type = (row < 1) ? 1 : (row < 3) ? 2 : 3;
            aliens.emplace_back(Position{.x = x, .y = y}, renderer, type);
        }
    }
}

void Game::MoveAliens() {
    for (auto& alien : aliens) {
        if (alienDirection == 1 && alien.position.x + alien.GetWidth() >= Constants::Window::Width) {
            alienDirection = -1;
            MoveAliensDown(4);
            break;
        }
        if (alienDirection == -1 && alien.position.x <= 0) {
            alienDirection = 1;
            MoveAliensDown(4);
            break;
        }
    }

    for (auto& alien : aliens) {
        alien.Update(alienDirection, deltaTime);
    }
}

void Game::MoveAliensDown(int distance) {
    for (auto& alien : aliens) {
        alien.position.y += distance;
    }
}

void Game::Reset() {
    // Return the ship to its starting position, clear transient state, and
    // resume gameplay after the ship's explosion has been acknowledged.
    ship->SetInitialPosition();
    ship->GetLasers().clear();
    shipDirection = 0;
    alienLasers.clear();
    explosions.clear();
    state = GameState::Playing;
}

void Game::ShootAlienLasers() {
    int randomIndex = Random::Int(0, static_cast<int>(aliens.size()) - 1);

    Laser laser;
    laser.position.x = aliens[randomIndex].position.x + Constants::Alien::Width / 2.0f - Constants::Laser::Width / 2.0f;
    laser.position.y = aliens[randomIndex].position.y + Constants::Alien::Height;
    alienLasers.push_back(laser);
}

void Game::DeleteInactiveAlienLasers() {
    alienLasers.erase(
        std::remove_if(alienLasers.begin(), alienLasers.end(),
                       [](const Laser& laser) { return laser.position.y > Constants::Window::Height; }),
        alienLasers.end());
}

void Game::CheckLaserCollision() {
    for (auto& shipLaser : ship->GetLasers()) {
        if (!shipLaser.active) {
            continue;
        }
        for (auto& obstacle : obstacles) {
            if (obstacle.CheckCollision(shipLaser, -1)) {
                shipLaser.active = false;
                break;
            }
        }
        if (!shipLaser.active) {
            continue;
        }
        for (auto it = aliens.begin(); it != aliens.end(); ++it) {
            const SDL_FRect laserRect = shipLaser.GetRect();
            const SDL_FRect alienRect = it->GetRect();
            if (SDL_HasRectIntersectionFloat(&laserRect, &alienRect)) {
                // Collision detected: remove the alien and consume the laser.
                explosions.emplace_back(it->position, renderer, false);

                aliens.erase(it);
                shipLaser.active = false;
                break;
            }
        }
    }

    for (auto it = alienLasers.begin(); it != alienLasers.end(); ++it) {
        if (!it->active) {
            continue;
        }
        for (auto& obstacle : obstacles) {
            if (obstacle.CheckCollision(*it, 1)) {
                it->active = false;
                break;
            }
        }
        if (!it->active) {
            continue;
        }
        if (ship->gotHit(it->GetRect())) {
            float explosionX = ship->GetRect().x;
            float explosionY = ship->GetRect().y;
            Position explosionPosition = { explosionX, explosionY };
            explosions.emplace_back(explosionPosition, renderer, true); // persistent explosion
            state = GameState::ShipExploding;
            it->active = false;
            if (lifes < 3) {
                state = GameState::GameOver;
            }
            break;
        }
    }
}

void Game::WriteGameOver() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    SDL_SetRenderScale(renderer, 2.0f, 2.0f);
    SDL_RenderDebugText(renderer, 170, 80, "GAME OVER");
    SDL_SetRenderScale(renderer, 1.0f, 1.0f);
}
