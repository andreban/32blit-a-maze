//
// Created by andre on 06/06/2021.
//

#ifndef GAME_TILE_H
#define GAME_TILE_H

#include <types/rect.hpp>

class Tile {
private:
    int32_t x_;
    int32_t y_;
    blit::Rect bounds_ = blit::Rect();
    bool collides_;
public:
    Tile(int32_t x, int32_t y, blit::Rect bounds, bool collides);
    bool collides();
    void setCollides(bool collides);
    int32_t x();
    int32_t y();
    blit::Rect* bounds();
};

#endif //GAME_TILE_H
