//
// Created by andre on 06/06/2021.
//

#include "Tile.h"

Tile::Tile(int32_t x, int32_t y, blit::Rect bounds, TileType tileType):
        x_(x), y_(y), bounds_(bounds), tileType_(tileType) {

}

bool Tile::collides() {
    return tileType_ == WALL || tileType_ == FLOODED;
}

int32_t Tile::x() {
    return x_;
}

int32_t Tile::y() {
    return y_;
}

blit::Rect *Tile::bounds() {
    return &bounds_;
}

TileType Tile::tileType() {
    return tileType_;
}

void Tile::setType(TileType tileType) {
    tileType_ = tileType;
}
