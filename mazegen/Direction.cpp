//
// Created by andre on 05/06/2021.
//
#include "Direction.h"

Direction opposite(Direction direction) {
    switch (direction) {
        case Direction::NORTH: return Direction::SOUTH;
        case Direction::EAST: return Direction::WEST;
        case Direction::SOUTH: return Direction::NORTH;
        case Direction::WEST: return Direction::EAST;
    }
}

int32_t vector_x(Direction direction) {
    switch (direction) {
        case NORTH:
        case SOUTH:
            return 0;
        case EAST:
            return 1;
        case WEST:
            return -1;
    }
}

int32_t vector_y(Direction direction) {
    switch (direction) {
        case EAST:
        case WEST:
            return 0;
        case SOUTH:
            return 1;
        case NORTH:
            return -1;
    }
}
