//
// Created by andre on 05/06/2021.
//

#include "Maze.h"

Maze::Maze(int32_t width, int32_t height): width_(width), height_(height) {
    for (int32_t y = 0; y < height_; y++) {
        for (int32_t x = 0; x < width_; x++) {
            cells.emplace_back(x, y);
        }
    }
}

int32_t Maze::position(int32_t x, int32_t y) const {
    return y * width_ + x;
}

int32_t Maze::width()  {
    return width_;
}

int32_t Maze::height()  {
    return height_;
}

Cell * Maze::cell_at(int32_t x, int32_t y)  {
    int32_t pos = position(x, y);
    return &cells[pos];
}

Cell * Maze::cell_at(int32_t x, int32_t y, Direction direction) {
    switch (direction) {
        case Direction::NORTH: return cell_at(x, y - 1);
        case Direction::EAST: return cell_at(x + 1, y);
        case Direction::SOUTH: return cell_at(x, y + 1);
        case Direction::WEST: return cell_at(x - 1 , y);
    }
}

void Maze::link(int32_t x, int32_t y, Direction direction) {
    Cell* cell = cell_at(x, y);
    cell->setOpen(direction, true);
    cell = cell_at(x, y, direction);
    cell->setOpen(opposite(direction), true);
}
