//
// Created by andre on 06/06/2021.
//

#include "Player.h"

Player::Player(int32_t x, int32_t y, int32_t size): mBounds(x, y, size, size) {

}

blit::Rect Player::bounds() {
    return mBounds;
}

void Player::move(int32_t x, int32_t y) {
    mBounds.x = x;
    mBounds.y = y;
}
