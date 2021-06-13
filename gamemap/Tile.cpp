//
// Created by andre on 06/06/2021.
//

#include "Tile.h"

Tile::Tile(int32_t x, int32_t y, blit::Rect bounds, TileType tileType):
        mX(x), mY(y), mBounds_(bounds), mTileType(tileType) {

}

bool Tile::collides() {
    return mTileType == WALL || mTileType == FLOODED;
}

int32_t Tile::x() {
    return mX;
}

int32_t Tile::y() {
    return mY;
}

blit::Rect *Tile::bounds() {
    return &mBounds_;
}

TileType Tile::tileType() {
    return mTileType;
}

void Tile::setType(TileType tileType) {
    mTileType = tileType;
}
