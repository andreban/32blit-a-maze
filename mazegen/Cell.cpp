//
// Created by andre on 05/06/2021.
//

#include "Cell.h"

int32_t Cell::x() {
    return x_;
}

int32_t Cell::y() {
    return y_;
}

void Cell::setXY(int32_t x, int32_t y)  {
    setX(x);
    setY(y);
}

void Cell::setX(int32_t x)  {
    x_ = x;
}

void Cell::setY(int32_t y)  {
    y_ = y;
}

void Cell::setOpen(Direction direction, bool open)  {
    if (open) {
        this->open_directions_ = this->open_directions_ | direction;
    } else {
        this->open_directions_ = this->open_directions_ & !direction;
    }
}

bool Cell::open(Direction direction)  {
    return (this->open_directions_ & direction) == direction;
}
