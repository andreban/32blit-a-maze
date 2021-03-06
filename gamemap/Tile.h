//
// Created by andre on 06/06/2021.
//

#ifndef GAME_TILE_H
#define GAME_TILE_H

#include <types/rect.hpp>

enum TileType {
    WALL = 1,
    FLOOR = 2,
    FLOODED = 4,
};

class Tile {
private:
    int32_t mX;
    int32_t mY;
    blit::Rect mBounds_ = blit::Rect();
    TileType mTileType = FLOOR;
public:
    Tile(int32_t x, int32_t y, blit::Rect bounds, TileType tileType);
    bool collides();
    void setType(TileType tileType);
    TileType tileType();
    int32_t x();
    int32_t y();
    blit::Rect* bounds();
};

#endif //GAME_TILE_H
