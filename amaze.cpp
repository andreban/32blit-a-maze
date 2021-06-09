#include "amaze.hpp"
#include "states/Game.h"

using namespace blit;

Game *game = nullptr;

void init() {
    set_screen_mode(ScreenMode::hires);
    game = Game::newGame();
}

void render(uint32_t time) {
    game->render(time);
}

void update(uint32_t time) {
    game->update(time);
}
