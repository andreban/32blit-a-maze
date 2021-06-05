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

