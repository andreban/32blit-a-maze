#include "game.hpp"
#include "mazegen/Maze.h"
#include "mazegen/MazeGen.h"
#include "gamemap/GameMap.h"
#include "entities/Player.h"
#include <types/rect.hpp>

using namespace blit;

Player buildPlayer(GameMap *gameMap) {
    Tile *tile = gameMap->tile_at(1, 1);
    int x = tile->bounds()->center().x;
    int y = tile->bounds()->center().y;
    return Player(x, y, 5);
}

GameMap buildMap() {
    Maze maze = binary_tree(20, 15);
    return GameMap::from_maze(&maze, 32, 32);
}

GameMap map = buildMap();
Player player = buildPlayer(&map);

void init() {
    set_screen_mode(ScreenMode::hires);
}

void render(uint32_t time) {
    screen.pen = Pen(0, 0, 0);
    screen.clear();
    screen.alpha = 255;
    screen.mask = nullptr;

    // Render Map
    for (int y = 0; y < map.height(); y++) {
        for (int x = 0; x < map.width(); x++) {
            Tile *tile = map.tile_at(x, y);
            if (tile->collides()) {
                screen.pen = Pen(0, 255, 0);
            } else {
                screen.pen = Pen(0, 0, 0);
            }
            screen.rectangle(*tile->bounds());
        }
    }

    // Render Player
    screen.pen = Pen(255, 0, 0);
    screen.rectangle(player.bounds());
}

void update(uint32_t time) {
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
    }
}
