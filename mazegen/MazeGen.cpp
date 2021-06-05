#include <random>
#include "MazeGen.h"

Maze binary_tree(int32_t width, int32_t height) {
    Maze maze = Maze(width, height);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (x == width - 1 && y == height -1) {
                continue;
            }

            Direction direction;
            if (x == width - 1) {
                direction = Direction::SOUTH;
            } else if (y == height - 1) {
                direction = Direction::EAST;
            } else {
                int rnd = rand() % 2;
                if (rnd == 0) {
                    direction = Direction::SOUTH;
                } else {
                    direction = Direction::EAST;
                }
            }

            maze.link(x, y, direction);
        }
    }
    return maze;
}

