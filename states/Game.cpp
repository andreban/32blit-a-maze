//
// Created by andre on 08/06/2021.
//

#include "Game.h"
#include "../mazegen/MazeGen.h"
#include "../mazegen/Distances.h"
#include "assets.hpp"

#include <utility>
using namespace blit;

const uint32_t TILE_TICK = 1000;
const uint32_t SPEED = 1;

Game::Game(GameMap map, Player player, Viewport viewport): mMap(std::move(map)), mPlayer(player), mViewport(viewport) {
    tiles = Surface::load(tileset);
}

void Game::update(uint32_t time) {
    Point moveAmount = Point(0, 0);
    if (pressed(DPAD_RIGHT)) {
        moveAmount.x+= SPEED;
    }
    if (pressed(DPAD_LEFT)) {
        moveAmount.x-= SPEED;
    }

    if (pressed(DPAD_UP)) {
        moveAmount.y-=SPEED;
    }
    if (pressed(DPAD_DOWN)) {
        moveAmount.y+=SPEED;
    }

    Rect movedPos = tryMove(moveAmount);
    mPlayer.move(movedPos.x, movedPos.y);

    Point playerTile = mMap.worldToTile(mPlayer.bounds().center());
    if (mMap.tileAt(playerTile.x, playerTile.y)->tileType() == FLOODED) {
        mGameOver = true;
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

    auto it = mBombs.begin();
    while (it < mBombs.end()) {
        it->tick(time);
        if (it->exploded()) {
            blit::Point bombTile = mMap.worldToTile(it->bounds().center());
            for (int y = bombTile.y - 1; y <= bombTile.y + 1; y++) {
                for (int x = bombTile.x - 1; x <= bombTile.x + 1; x++) {
                    Tile *tile = mMap.tileAt(x, y);
                    if (tile->tileType() == WALL && tile->bounds()->intersects(it->blastBounds())) {
                        makeFloor(tile);
                    }
                }
            }
            it = mBombs.erase(it);
        } else {
            it++;
        }
    }

    if ((buttons.pressed & A) && mPlayer.useBomb()) {
        mBombs.emplace_back(mPlayer.bounds(), time);
    }
}

void Game::render(uint32_t time) {
    screen.pen = Pen(0, 0, 0);
    screen.clear();
    screen.alpha = 255;
    screen.mask = nullptr;

    mViewport.update(mPlayer.bounds().center());

    // Render Walls
    // TODO: Render only tiles that will actually be on the screen.
    //   blit::Point playerTile = mMap.worldToTile(mPlayer.bounds().center());
    for (int y = 0; y < mMap.size().h; y++) {
        for (int x = 0; x < mMap.size().w; x++) {
            Tile *tile = mMap.tileAt(x, y);
            if (tile->tileType() == WALL) {
                screen.stretch_blit(this-> tiles, this->wall, mViewport.translate(*tile->bounds()));
            } else if (mMap.isFlooding(x, y)) {
                screen.stretch_blit(this-> tiles, this->flooding, mViewport.translate(*tile->bounds()));
            } else if (tile-> tileType() == FLOODED) {
                screen.stretch_blit(this-> tiles, this->flooded, mViewport.translate(*tile->bounds()));
            } else {
                screen.pen = Pen(0, 0, 0);
                screen.rectangle(mViewport.translate(*tile->bounds()));
            }

            if (mMap.exit().x == x && mMap.exit().y == y){
                screen.stretch_blit(this->tiles, this->exit, mViewport.translate(*tile->bounds()));
            }
        }
    }

    // Render bombs
    for (auto bomb: mBombs) {
        screen.stretch_blit(this->tiles, this->bomb, mViewport.translate(bomb.bounds()));
    }

    // Render Player
    screen.pen = Pen(255, 0, 0);
    screen.circle(mViewport.translate(mPlayer.bounds()).center(), mPlayer.bounds().w / 2);
//    screen.rectangle(mViewport.translate(mPlayer.bounds()));
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

void Game::makeFloor(Tile *tile) {
    if (tile->tileType() != WALL ||
            tile->y() == 0 || tile->y() == mMap.size().h - 1 ||
            tile->x() == 0 || tile->x() == mMap.size().w - 1) {
        return;
    }
    tile->setType(FLOOR);
    for (int y = tile->y() - 1; y <= tile->y() + 1; y++) {
        for (int x = tile->x() - 1; x <= tile->x() + 1; x++) {
            Tile *nextTile = mMap.tileAt(x, y);
            if (nextTile->tileType() == FLOODED) {
                mMap.setFlooding(tile->x(), tile->y());
                return;
            }
        }
    }
}

Tile* Game::canMove(blit::Rect next) {
    blit::Point playerTile = mMap.worldToTile(next.center());
    for (int y = playerTile.y - 1; y <= playerTile.y + 1; y++) {
        for (int x = playerTile.x - 1; x <= playerTile.x + 1; x++) {
            Tile *tile = mMap.tileAt(x, y);
            if (tile->collides() && tile->bounds()->intersects(next)) {
                return tile;
            }
        }
    }
    return nullptr;
}

blit::Rect Game::tryMove(blit::Point amount) {
    Rect next = mPlayer.bounds();

    // Try moving along the X axis.
    Rect nextX = blit::Rect(next.x + amount.x, next.y, next.w, next.h);
    Tile* collided = canMove(nextX);

    // If collided, check how much we can move along X.
    if (collided != nullptr) {
        if (amount.x > 0) {
            next.x = collided->bounds()->x - next.w - 1;
        } else {
            next.x = collided->bounds()->x + collided->bounds()->w + 1;
        }
    } else {
        next.x = nextX.x;
    }

    // Try moving along the Y axis.
    Rect nextY = blit::Rect(next.x, next.y + amount.y, next.w, next.h);
    collided = canMove(nextY);
    // If collided, check how much we can move along Y.
    if (collided != nullptr) {
        if (amount.y > 0) {
            next.y = collided->bounds()->y - next.h - 1;
        } else {
            next.y = collided->bounds()->y + collided->bounds()->h + 1;
        }
    } else {
        next.y = nextY.y;
    }

    return next;
}
