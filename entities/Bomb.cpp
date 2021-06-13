//
// Created by andre on 13/06/2021.
//

#include "Bomb.h"

Bomb::Bomb(blit::Rect bounds, uint32_t created): mBounds(bounds), mCreated(created) {

}

void Bomb::tick(uint32_t time) {
    if (time - mCreated > BOMB_TIMER) {
        mExploded = true;
    }
}

bool Bomb::exploded() {
    return mExploded;
}

blit::Rect Bomb::bounds() {
    return mBounds;
}

blit::Rect Bomb::blastBounds() {
    return blit::Rect(mBounds.x - 10, mBounds.y - 10, mBounds.w + 20, mBounds.h + 20);
}
