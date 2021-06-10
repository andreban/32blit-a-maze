//
// Created by andre on 08/06/2021.
//

#ifndef AMAZE_GAME_H
#define AMAZE_GAME_H

#include "32blit.hpp"
#include "../gamemap/GameMap.h"
#include "../entities/Player.h"
#include "../entities/Viewport.h"

class Game {
private:
    GameMap map;
    Player player;
    Viewport viewport;
    bool victory_ = false;
    bool gameOver_ = false;
    uint32_t lastUpdate = 0;
public:
    Game(GameMap map, Player player, Viewport viewport);
    void update(uint32_t time);
    void render(uint32_t time);
    static Game* newGame();
    bool victory() {
        return victory_;
    }

    bool gameOver() {
        return gameOver_;
    }
};


#endif //AMAZE_GAME_H
