#include <SDL3/SDL.h>
#include "Game.h"

int main(int argc, char* argv[]) {

    Game game = Game();
    if (!game.InitializeWindow()) {
        return -1;
    }

    while (game.running) {
        game.HandleInput();
        game.Update();
        game.Draw();
    }

    return 0;
}
