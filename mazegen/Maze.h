//
// Created by andre on 05/06/2021.
//

#ifndef GAME_MAZE_H
#define GAME_MAZE_H

#include "Cell.h"
#include <vector>

class Maze {
private:
    int32_t width_;
    int32_t height_;
    std::vector<Cell> cells;

    int32_t position(int32_t x, int32_t y) const {
        return y * width_ + x;
    }
public:
    Maze(int32_t width, int32_t height): width_(width), height_(height) {
        for (int32_t y = 0; y < height_; y++) {
            for (int32_t x = 0; x < width_; x++) {
                cells.emplace_back(x, y);
            }
        }
    }

    int32_t width() {
        return width_;
    }

    int32_t height() {
        return height_;
    }

    Cell* cell_at(int32_t x, int32_t y) {
        int32_t pos = position(x, y);
        return &cells[pos];
    }

    Cell* cell_at(int32_t x, int32_t y, Direction direction) {
        switch (direction) {
            case Direction::NORTH: return cell_at(x, y - 1);
            case Direction::EAST: return cell_at(x + 1, y);
            case Direction::SOUTH: return cell_at(x, y + 1);
            case Direction::WEST: return cell_at(x - 1 , y);
        }
    }

    void link(int32_t x, int32_t y, Direction direction) {
        Cell* cell = cell_at(x, y);
        cell->setOpen(direction, true);
        cell = cell_at(x, y, direction);
        cell->setOpen(opposite(direction), true);
    }
};


#endif //GAME_MAZE_H
