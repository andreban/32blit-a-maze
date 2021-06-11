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
    blit::Size mSize;
    int32_t mTileSize;
    int32_t mWallSize;
    blit::Size mPixelSize;
    blit::Point mExit;
    std::vector<Tile> mTiles;
    std::vector<blit::Point> mFlooding;
    int32_t tilePos(int32_t x, int32_t y) const;
public:
    GameMap(blit::Size mSize, int32_t tileSize, int32_t wallSize, blit::Point start, blit::Point exit);
    blit::Size size();
    blit::Point exit();
    blit::Size pixelSize();
    blit::Point worldToTile(blit::Point world);
    Tile* tileAt(int32_t pos);
    Tile* tileAt(int32_t x, int32_t y);
    bool isFlooding(int32_t x, int32_t y);
    void flood();
    static GameMap fromMaze(Maze *maze, int32_t tile_size, int32_t wall_size, blit::Point start, blit::Point exit);
};

#endif //GAME_GAMEMAP_H
