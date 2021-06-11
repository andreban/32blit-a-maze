//
// Created by andre on 06/06/2021.
//

#include "GameMap.h"

GameMap::GameMap(blit::Size size, int32_t tileSize, int32_t wallSize, blit::Point start, blit::Point exit):
        mSize(size), mTileSize(tileSize), mWallSize(wallSize), mExit(exit) {
    int32_t tile_start_y = 0;
    int32_t tile_start_x = 0;
    for (int y = 0; y < size.h; y++) {
        int32_t tile_height = (y & 1) == 0 ? wallSize : tileSize;
        tile_start_x = 0;
        for (int x = 0; x < size.w; x++) {
            int32_t tile_width = (x & 1) == 0 ? wallSize : tileSize;
            TileType tileType = TileType::FLOOR;
            if (!((x & 1) == 1 && (y & 1) == 1)) {
                tileType = TileType::WALL;
            };
            blit::Rect bounds = blit::Rect(tile_start_x, tile_start_y, tile_width, tile_height);
            Tile tile = Tile(x, y, bounds, tileType);
            mTiles.push_back(tile);
            tile_start_x += tile_width;
        }
        tile_start_y += tile_height;
    }
    mPixelSize = blit::Size(tile_start_x, tile_start_y);
    mFlooding.push_back(start);
}

GameMap GameMap::fromMaze(Maze *maze, int32_t tile_size, int32_t wall_size, blit::Point start, blit::Point exit) {
    int32_t map_width = maze->width() * 2 + 1;
    int32_t map_height = maze->height() * 2 + 1;
    GameMap gameMap = GameMap(blit::Size(map_width, map_height), tile_size, wall_size, start, exit);
    for (int y = 0; y < maze->height(); y++) {
        for (int x  = 0; x < maze->width(); x++) {
            Cell *cell = maze->cell_at(x, y);
            if (cell->open(Direction::NORTH)) {
                gameMap.tileAt(x * 2 + 1, y * 2)->setType(TileType::FLOOR);
            }

            // Checking South shouldn't be needed, but we do it anyway.
            if (cell->open(Direction::SOUTH)) {
                gameMap.tileAt(x * 2 + 1, y * 2 + 2)->setType(TileType::FLOOR);
            }

            if (cell->open(Direction::WEST)) {
                gameMap.tileAt(x * 2, y * 2 + 1)->setType(TileType::FLOOR);
            }

            // Checking East shouldn't be needed, but we do it anyway.
            if (cell->open(Direction::EAST)) {
                gameMap.tileAt(x * 2 + 2, y * 2 + 1)->setType(TileType::FLOOR);
            }
        }
    }
    return gameMap;
}

blit::Size GameMap::size() {
    return mSize;
}

Tile *GameMap::tileAt(int32_t x, int32_t y) {
    return tileAt(tilePos(x, y));
}

blit::Size GameMap::pixelSize() {
    return mPixelSize;
}

blit::Point GameMap::exit() {
    return mExit;
}

Tile *GameMap::tileAt(int32_t pos) {
    return &mTiles[pos];
}

int32_t GameMap::tilePos(int32_t x, int32_t y) const {
    return y * mSize.w + x;
}

bool GameMap::isFlooding(int32_t x, int32_t y) {
    return std::find(mFlooding.begin(), mFlooding.end(), blit::Point(x, y)) != mFlooding.end();
}

void GameMap::flood() {
    std::vector<blit::Point> nextFlooding;
    for (auto pos: mFlooding) {
        Tile *tile = tileAt(pos.x, pos.y);
        tile->setType(FLOODED);
        for (auto direction: DIRECTIONS) {
            Tile *nextTile = tileAt(pos.x + vector_x(direction), pos.y + vector_y(direction));
            if (nextTile->tileType() == FLOOR) {
                nextFlooding.emplace_back(nextTile->x(), nextTile->y());
            }
        }
    }
    mFlooding = nextFlooding;
}

blit::Point GameMap::worldToTile(blit::Point world) {
    int32_t tileX = world.x / (mTileSize + mWallSize) * 2;
    if (world.x % (mTileSize + mWallSize) > mTileSize) {
        tileX += 1;
    }

    int32_t tileY = world.y / (mTileSize + mWallSize) * 2;
    if (world.y % (mTileSize + mWallSize) > mTileSize) {
        tileY += 1;
    }

    return blit::Point(tileX ,tileY);
}
