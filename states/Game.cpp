//
// Created by andre on 08/06/2021.
//

#include "Game.h"
#include "../mazegen/MazeGen.h"
#include "../mazegen/Distances.h"

#include <utility>
using namespace blit;

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

    if (!map.collides(next)) {
        player.move(next.x, next.y);
        Tile *exitTile = map.tile_at(map.exit().x, map.exit().y);
        if (player.bounds().intersects(*exitTile->bounds())){
            victory_ = true;
        }
    }
}

void Game::render(uint32_t time) {
    screen.pen = Pen(0, 0, 0);
    screen.clear();
    screen.alpha = 255;
    screen.mask = nullptr;

    viewport.update(player.bounds().center());

    // Render Map
    for (int y = 0; y < map.height(); y++) {
        for (int x = 0; x < map.width(); x++) {
            Tile *tile = map.tile_at(x, y);
            if (tile->collides()) {
                screen.pen = Pen(0, 255, 0);
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
    Distances distances = Distances::calculate_distances(&maze, Point(start_cell_x, start_cell_y));
    Point exit = Point(distances.maxPoint().x * 2 + 1, distances.maxPoint().y * 2 + 1);

    GameMap map = GameMap::from_maze(&maze, 32, 32, exit);


    int32_t start_tile_x = start_cell_x * 2 + 1;
    int32_t start_tile_y = start_cell_y * 2 + 1;

    Tile *tile = map.tile_at(start_tile_x, start_tile_y);
    int x = tile->bounds()->center().x - 4;
    int y = tile->bounds()->center().y - 4;
    Player player = Player(x, y, 8);
    Viewport viewport = Viewport(screen.bounds, map.pixelSize());
    return new Game(map, player, viewport);
}
