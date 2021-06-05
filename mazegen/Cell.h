//
// Created by andre on 05/06/2021.
//

#ifndef GAME_CELL_H
#define GAME_CELL_H

#include <cstdint>
#include "Direction.h"

class Cell {
private:
    int32_t x_;
    int32_t y_;
    uint8_t open_directions_ = 0;
public:
    Cell(int32_t x, int32_t y): x_(x), y_(y) {

    }

    int32_t x() {
        return x_;
    }

    int32_t y() {
        return y_;
    }

    void setXY(int32_t x, int32_t y) {
        setX(x);
        setY(y);
    }

    void setX(int32_t x) {
        x_ = x;
    }

    void setY(int32_t y) {
        y_ = y;
    }

    void setOpen(Direction direction, bool open) {
        if (open) {
            this->open_directions_ = this->open_directions_ | direction;
        } else {
            this->open_directions_ = this->open_directions_ & !direction;
        }
    }

    bool open(Direction direction) {
        return (this->open_directions_ & direction) == direction;
    }
};


#endif //GAME_CELL_H
