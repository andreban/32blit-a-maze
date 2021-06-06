//
// Created by andre on 06/06/2021.
//

#include "Player.h"

Player::Player(int32_t x, int32_t y, int32_t size): bounds_(x, y, size, size) {

}

blit::Rect Player::bounds() {
    return bounds_;
}

void Player::move(int32_t x, int32_t y) {
    bounds_.x = x;
    bounds_.y = y;
}
