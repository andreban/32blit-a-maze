//
// Created by andre on 06/06/2021.
//

#include "Tile.h"

Tile::Tile(int32_t x, int32_t y, blit::Rect bounds, bool collides):
        x_(x), y_(y), bounds_(bounds), collides_(collides) {

}

bool Tile::collides() {
    return collides_;
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

void Tile::setCollides(bool collides) {
    collides_ = collides;
}
