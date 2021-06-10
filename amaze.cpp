#include "amaze.hpp"
#include "states/Game.h"
#include "states/GameOver.h"
#include "states/MainMenu.h"

using namespace blit;

enum GameState {
    MAIN_MENU,
    GAME,
    GAME_OVER,
};

GameState gameState = MAIN_MENU;
Game *game = nullptr;
GameOver gameOver = GameOver();
MainMenu mainMenu = MainMenu();

void init() {
    set_screen_mode(ScreenMode::hires);
}

void render(uint32_t time) {
    switch (gameState) {
        case MAIN_MENU:
            mainMenu.render(time);
            break;
        case GAME:
            game->render(time);
            break;
        case GAME_OVER:
            gameOver.render(time);
    }
}

void update(uint32_t time) {
    switch (gameState) {
        case MAIN_MENU:
            mainMenu.update(time);
            if (mainMenu.newGame()) {
                srand(time);
                game = Game::newGame();
                gameState = GAME;
            }
            break;
        case GAME:
            game->update(time);
            if (game->gameOver()) {
                gameOver.reset();
                gameState = GAME_OVER;
            } else if (game->victory()) {
                game = Game::newGame();
            }
            break;
        case GAME_OVER:
            gameOver.update(time);
            if (gameOver.done()) {
                mainMenu.reset();
                gameState = MAIN_MENU;
            }
    }
}
