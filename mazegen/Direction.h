//
// Created by andre on 05/06/2021.
//

#ifndef GAME_DIRECTION_H
#define GAME_DIRECTION_H

#include <cstdint>

enum Direction {
    NORTH = 1, EAST = 2, SOUTH = 4, WEST = 8,
};

Direction opposite(Direction direction);
int32_t vector_x(Direction direction);
int32_t vector_y(Direction direction);

#endif //GAME_DIRECTION_H
