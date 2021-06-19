//
// Created by andre on 08/06/2021.
//

#ifndef AMAZE_GAME_H
#define AMAZE_GAME_H

#include "32blit.hpp"
#include "../gamemap/GameMap.h"
#include "../entities/Player.h"
#include "../entities/Viewport.h"
#include "../entities/Bomb.h"

class Game {
private:
    GameMap mMap;
    Player mPlayer;
    Viewport mViewport;
    bool mVictory = false;
    bool mGameOver = false;
    uint32_t mLastUpdate = 0;
    std::vector<Bomb> mBombs;
    blit::Surface *tiles;
    blit::Rect wall = blit::Rect(16, 416, 16, 16);
    blit::Rect exit = blit::Rect(176, 464, 16, 16);
    blit::Rect bomb = blit::Rect(112, 544, 16, 16);
    blit::Rect flooded = blit::Rect(6 * 16, 12 * 16, 16, 16);
    blit::Rect flooding = blit::Rect(6 * 16, 12 * 16, 16, 16);//blit::Rect(16, 16, 16, 16);
    void makeFloor(Tile *tile);
public:
    Game(GameMap map, Player player, Viewport viewport);
    void update(uint32_t time);
    void render(uint32_t time);
    blit::Rect tryMove(blit::Point amount);
    Tile* canMove(blit::Rect next);
    static Game* newGame();
    bool victory() {
        return mVictory;
    }

    bool gameOver() {
        return mGameOver;
    }
};

#endif //AMAZE_GAME_H
