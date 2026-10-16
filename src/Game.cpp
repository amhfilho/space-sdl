#include "Game.h"

#include "Constants.h"
#include "MisteryShip.h"
#include "Explosion.h"
#include "Random.h"

Game::Game()
    : running(true)
    , window(nullptr)
    , renderer(nullptr)
    , shipDirection(0)
    , alienDirection(1)
    , lastLaserShotTime(0)
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

    ship.emplace();
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
                if (state == GameState::ShipExploding) {
                    Reset();
                }
                else if (event.key.key == SDLK_SPACE && !event.key.repeat) {
                    ship->FireLaser();
                }
                break;
        }

        if (state == GameState::ShipExploding) {
            // Gameplay is frozen until the player presses a key (handled above).
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
        // Gameplay is frozen; wait for the player to press a key (see HandleInput).
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

    if (state == GameState::Playing) {
        ship->Draw(renderer, 0.0f);
    }

    for (int i = lifes; i > 0; i--) {
        
        ship->Draw(renderer, 0.0f);
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
        Constants::Window::Height - (Constants::Window::Height - Constants::Space::Height),
        Constants::Window::Width,
        Constants::Window::Height - (Constants::Window::Height - Constants::Space::Height));

    SDL_RenderPresent(renderer);
}

Game::~Game() {
    aliens.clear();
    Alien::ClearTextureCache();
    misteryShip.reset();
    explosions.clear();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::CreateAllObstacles() {
    obstacles.clear();
    int obstacleWidth = Obstacle::grid[0].size() * Constants::Block::Width;
    int obstacleHeight = Obstacle::grid.size() * Constants::Block::Height;
    float gap = (Constants::Window::Width - (4 * obstacleWidth)) / 5; // Calculate the gap between obstacles

    for (int i = 0; i < 4; ++i) {
        float offsetX = (i + 1) * gap + i * obstacleWidth;

        Position position = { offsetX, Constants::Space::Height - Constants::Ship::ShipHeight - obstacleHeight*3 };
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
    ship->position = { Constants::Ship::BaseStartX, Constants::Ship::BaseStartY };
    ship->GetLasers().clear();
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
            float explosionX = ship->position.x + Constants::Ship::BaseWidth / 2.0f - Constants::Ship::BaseWidth / 2.0f;
            float explosionY = ship->position.y - Constants::Ship::ShipHeight;
            Position explosionPosition = { explosionX, explosionY };
            explosions.emplace_back(explosionPosition, renderer, true); // persistent explosion
            state = GameState::ShipExploding;
            it->active = false;
            break;
        }
    }
}
