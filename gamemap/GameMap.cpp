//
// Created by andre on 06/06/2021.
//

#include "GameMap.h"

GameMap::GameMap(int32_t width, int32_t height, int32_t tile_size, int32_t wall_size, blit::Point exit):
        width_(width), height_(height), exit_(exit) {
    int32_t tile_start_y = 0;
    int32_t tile_start_x = 0;
    for (int y = 0; y < height; y++) {
        int32_t tile_height = (y & 1) == 0 ? wall_size : tile_size;
        tile_start_x = 0;
        for (int x = 0; x < width; x++) {
            int32_t tile_width = (x & 1) == 0 ? wall_size : tile_size;
            TileType tileType = TileType::FLOOR;
            if (!((x & 1) == 1 && (y & 1) == 1)) {
                tileType = TileType::WALL;
            };
            blit::Rect bounds = blit::Rect(tile_start_x, tile_start_y, tile_width, tile_height);
            Tile tile = Tile(x, y, bounds, tileType);
            tiles.push_back(tile);
            tile_start_x += tile_width;
        }
        tile_start_y += tile_height;
    }
    pixel_size_ = blit::Size(tile_start_x, tile_start_y);
}

GameMap GameMap::from_maze(Maze *maze, int32_t tile_size, int32_t wall_size, blit::Point exit) {
    int32_t map_width = maze->width() * 2 + 1;
    int32_t map_height = maze->height() * 2 + 1;
    GameMap gameMap = GameMap(map_width, map_height, tile_size, wall_size, exit);
    for (int y = 0; y < maze->height(); y++) {
        for (int x  = 0; x < maze->width(); x++) {
            Cell *cell = maze->cell_at(x, y);
            if (cell->open(Direction::NORTH)) {
                gameMap.tile_at(x * 2 + 1, y * 2)->setType(TileType::FLOOR);
            }

            // Checking South shouldn't be needed, but we do it anyway.
            if (cell->open(Direction::SOUTH)) {
                gameMap.tile_at(x * 2 + 1, y * 2 + 2)->setType(TileType::FLOOR);
            }

            if (cell->open(Direction::WEST)) {
                gameMap.tile_at(x * 2, y * 2 + 1)->setType(TileType::FLOOR);
            }

            // Checking East shouldn't be needed, but we do it anyway.
            if (cell->open(Direction::EAST)) {
                gameMap.tile_at(x * 2 + 2, y * 2 + 1)->setType(TileType::FLOOR);
            }
        }
    }
    return gameMap;
}

int32_t GameMap::width() {
    return width_;
}

int32_t GameMap::height() {
    return height_;
}

Tile *GameMap::tile_at(int32_t x, int32_t y) {
    return &tiles[y * width_ + x];
}

Tile* GameMap::collides(blit::Rect obj) {
    for (Tile tile: tiles) {
        if (tile.collides() && tile.bounds()->intersects(obj)) {
            return &tile;
        }
    }
    return nullptr;
}

blit::Size GameMap::pixelSize() {
    return pixel_size_;
}

blit::Point GameMap::exit() {
    return exit_;
}
