//
// Created by andre on 08/06/2021.
//

#include "Game.h"
#include "../mazegen/MazeGen.h"
#include "../mazegen/Distances.h"

#include <utility>
using namespace blit;

const uint32_t TILE_TICK = 1000;

Game::Game(GameMap map, Player player, Viewport viewport): mMap(std::move(map)), mPlayer(player), mViewport(viewport) {

}

void Game::update(uint32_t time) {
    blit::Rect next = blit::Rect(mPlayer.bounds().tl(), mPlayer.bounds().br());
    if (pressed(DPAD_RIGHT)) {
        next.x++;
    }
    if (pressed(DPAD_LEFT)) {
        next.x--;
    }
    if (pressed(DPAD_UP)) {
        next.y--;
    }
    if (pressed(DPAD_DOWN)) {
        next.y++;
    }

    blit::Point playerTile = mMap.worldToTile(mPlayer.bounds().center());
    bool collided = false;
    for (int y = playerTile.y - 1; y <= playerTile.y + 1; y++) {
        for (int x = playerTile.x - 1; x <= playerTile.x + 1; x++) {
            Tile *tile = mMap.tileAt(x, y);
            if (tile->collides() && tile->bounds()->intersects(next)) {
                collided = true;
                if (tile->tileType() == FLOODED) {
                    mGameOver = true;
                }
            }
        }
    }

    if (!collided) {
        mPlayer.move(next.x, next.y);
    }

    Tile *exitTile = mMap.tileAt(mMap.exit().x, mMap.exit().y);
    if (mPlayer.bounds().intersects(*exitTile->bounds())){
        mVictory = true;
    }

    if (mLastUpdate == 0) {
        mLastUpdate = time;
    } else if (time - mLastUpdate > TILE_TICK) {
        mMap.flood();
        mLastUpdate = time;
    }
}

void Game::render(uint32_t time) {
    screen.pen = Pen(0, 0, 0);
    screen.clear();
    screen.alpha = 255;
    screen.mask = nullptr;

    mViewport.update(mPlayer.bounds().center());

    // TODO: Render only tiles that will actually be on the screen.
    //   blit::Point playerTile = mMap.worldToTile(mPlayer.bounds().center());
    for (int y = 0; y < mMap.size().h; y++) {
        for (int x = 0; x < mMap.size().w; x++) {
            Tile *tile = mMap.tileAt(x, y);
            if (tile->tileType() == WALL) {
                screen.pen = Pen(0, 255, 0);
            } else if (mMap.isFlooding(x, y)) {
                screen.pen = Pen(10, 10, 100);
            } else if (tile-> tileType() == FLOODED) {
                screen.pen = Pen(100, 100, 255);
            } else if (mMap.exit().x == x && mMap.exit().y == y){
                screen.pen = Pen(255, 0, 0);
            } else {
                screen.pen = Pen(0, 0, 0);
            }
            screen.rectangle(mViewport.translate(*tile->bounds()));
        }
    }

    // Render Player
    screen.pen = Pen(255, 0, 0);
    screen.rectangle(mViewport.translate(mPlayer.bounds()));
}

Game* Game::newGame() {
    Maze maze = binary_tree(20, 15);
    int32_t start_cell_x = rand() % maze.width();
    int32_t start_cell_y = rand() % maze.height();
    int32_t start_tile_x = start_cell_x * 2 + 1;
    int32_t start_tile_y = start_cell_y * 2 + 1;

    Distances distances = Distances::calculate_distances(&maze, Point(start_cell_x, start_cell_y));
    Point start = Point(start_tile_x, start_tile_y);
    Point exit = Point(distances.maxPoint().x * 2 + 1, distances.maxPoint().y * 2 + 1);

    GameMap map = GameMap::fromMaze(&maze, 32, 32, start, exit);

    Tile *tile = map.tileAt(start_tile_x, start_tile_y);
    int x = tile->bounds()->center().x - 4;
    int y = tile->bounds()->center().y - 4;
    Player player = Player(x, y, 8);
    Viewport viewport = Viewport(screen.bounds, map.pixelSize());
    return new Game(map, player, viewport);
}
