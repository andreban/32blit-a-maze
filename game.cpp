#include "game.hpp"
#include "mazegen/Maze.h"
#include "mazegen/MazeGen.h"

using namespace blit;
const int TILE_SIZE = 16;

Maze maze = binary_tree(20, 15);

void init() {
    set_screen_mode(ScreenMode::hires);
}

void render(uint32_t time) {
    screen.pen = Pen(0, 0, 0);
    screen.clear();
    screen.alpha = 255;
    screen.mask = nullptr;

    for (int y = 0; y < maze.height(); y++) {
        for (int x = 0; x < maze.width(); x++) {
            Cell *cell = maze.cell_at(x, y);
            screen.pen = Pen(0, 255, 0);
            if (!cell->open(Direction::NORTH)) {
                screen.line(
                        Point(x * TILE_SIZE, y * TILE_SIZE),
                        Point(x * TILE_SIZE + TILE_SIZE, y * TILE_SIZE)
                );
            }

            if (!cell->open(Direction::EAST)) {
                screen.line(
                        Point(x * TILE_SIZE + TILE_SIZE - 1, y * TILE_SIZE),
                        Point(x * TILE_SIZE + TILE_SIZE - 1, y * TILE_SIZE + TILE_SIZE)
                );
            }

            if (!cell->open(Direction::SOUTH)) {
                screen.line(
                        Point(x * TILE_SIZE, y * TILE_SIZE + TILE_SIZE - 1),
                        Point(x * TILE_SIZE + TILE_SIZE, y * TILE_SIZE + TILE_SIZE - 1)
                );
            }

            if (!cell->open(Direction::WEST)) {
                screen.line(
                        Point(x * TILE_SIZE, y * TILE_SIZE),
                        Point(x * TILE_SIZE, y * TILE_SIZE + TILE_SIZE)
                );
            }

        }
    }
}

void update(uint32_t time) {
}
