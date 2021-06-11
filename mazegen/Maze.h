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

    int32_t position(int32_t x, int32_t y) const;
public:
    Maze(int32_t width, int32_t height);
    int32_t width();
    int32_t height();
    Cell* cell_at(int32_t x, int32_t y);
    Cell* cell_at(int32_t x, int32_t y, Direction direction);
    void link(int32_t x, int32_t y, Direction direction);
};

#endif //GAME_MAZE_H
