//
// Created by andre on 13/06/2021.
//

#ifndef AMAZE_BOMB_H
#define AMAZE_BOMB_H

#include <cstdint>
#include <types/rect.hpp>

// Bomb explodes after 1 second.
const uint32_t BOMB_TIMER = 2000L;

class Bomb {
private:
    uint32_t mCreated;
    bool mExploded = false;
    blit::Rect mBounds;
public:
    explicit Bomb(blit::Rect bounds, uint32_t created);
    void tick(uint32_t time);
    bool exploded();
    blit::Rect bounds();
    blit::Rect blastBounds();
};

#endif //AMAZE_BOMB_H
