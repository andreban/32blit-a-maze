//
// Created by andre on 08/06/2021.
//

#include "Game.h"
#include "../mazegen/MazeGen.h"
#include "../mazegen/Distances.h"

#include <utility>
using namespace blit;

const uint32_t TILE_TICK = 1000;

Game::Game(GameMap map, Player player, Viewport viewport): map(std::move(map)), player(player), viewport(viewport) {

}

void Game::update(uint32_t time) {
    blit::Rect next = blit::Rect(player.bounds().tl(), player.bounds().br());
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

    blit::Point playerTile = map.worldToTile(player.bounds().center());
    bool collided = false;
    for (int y = playerTile.y - 1; y <= playerTile.y + 1; y++) {
        for (int x = playerTile.x - 1; x <= playerTile.x + 1; x++) {
            Tile *tile = map.tileAt(x, y);
            if (tile->collides() && tile->bounds()->intersects(next)) {
                collided = true;
                if (tile->tileType() == FLOODED) {
                    gameOver_ = true;
                }
            }
        }
    }

    if (!collided) {
        player.move(next.x, next.y);
    }

    Tile *exitTile = map.tileAt(map.exit().x, map.exit().y);
    if (player.bounds().intersects(*exitTile->bounds())){
        victory_ = true;
    }

    if (lastUpdate == 0) {
        lastUpdate = time;
    } else if (time - lastUpdate > TILE_TICK) {
        map.flood();
        lastUpdate = time;
    }
}

void Game::render(uint32_t time) {
    screen.pen = Pen(0, 0, 0);
    screen.clear();
    screen.alpha = 255;
    screen.mask = nullptr;

    viewport.update(player.bounds().center());

    // TODO: Render only tiles that will actually be on the screen.
    //   blit::Point playerTile = map.worldToTile(player.bounds().center());
    for (int y = 0; y < map.size().h; y++) {
        for (int x = 0; x < map.size().w; x++) {
            Tile *tile = map.tileAt(x, y);
            if (tile->tileType() == WALL) {
                screen.pen = Pen(0, 255, 0);
            } else if (map.isFlooding(x, y)) {
                screen.pen = Pen(10, 10, 100);
            } else if (tile-> tileType() == FLOODED) {
                screen.pen = Pen(100, 100, 255);
            } else if (map.exit().x == x && map.exit().y == y){
                screen.pen = Pen(255, 0, 0);
            } else {
                screen.pen = Pen(0, 0, 0);
            }
            screen.rectangle(viewport.translate(*tile->bounds()));
        }
    }

    // Render Player
    screen.pen = Pen(255, 0, 0);
    screen.rectangle(viewport.translate(player.bounds()));
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
