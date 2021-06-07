//
// Created by andre on 06/06/2021.
//

#ifndef GAME_GAMEMAP_H
#define GAME_GAMEMAP_H

#include <types/rect.hpp>
#include "../mazegen/Maze.h"
#include "Tile.h"

class GameMap {
private:
    int32_t width_;
    int32_t height_;
    blit::Size pixel_size_;
    std::vector<Tile> tiles;
public:
    GameMap(int32_t width, int32_t height, int32_t tile_size, int32_t wall_size);
    int32_t width();
    int32_t height();
    blit::Size pixelSize();
    Tile* tile_at(int32_t x, int32_t y);
    bool collides(blit::Rect obj);
    static GameMap from_maze(Maze *maze, int32_t tile_size, int32_t wall_size);
};

#endif //GAME_GAMEMAP_H
