//
// Created by andre on 06/06/2021.
//

#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include <types/rect.hpp>

class Player {
private:
    blit::Rect mBounds;
public:
    Player(int32_t x, int32_t y, int32_t size);
    blit::Rect bounds();
    void move(int32_t x, int32_t y);
};

#endif //GAME_PLAYER_H
