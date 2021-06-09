//
// Created by andre on 08/06/2021.
//

#include "Distances.h"

#include <utility>

Distances::Distances(int32_t width, int32_t height, std::vector<int32_t> distances)
    : width_(width), height_(height), distances(std::move(distances)){

}

int32_t Distances::width() {
    return width_;
}

int32_t Distances::height() {
    return height_;
}

int32_t Distances::max() {
    int max_distance = 0;
    for (int y = 0; y < height(); y++) {
        for (int x = 0; x < width(); x++) {
            max_distance = std::max(max_distance, distanceAt(x, y));
        }
    }
    return max_distance;
}

int32_t Distances::distanceAt(int32_t x, int32_t y) {
    return distances[y * width() + x];
}

void distance(Maze *maze, blit::Point position, int32_t score, std::vector<int32_t> &scores, std::vector<bool> &visited){
    int32_t pos = position.y * maze->width() + position.x;

    if (visited.at(pos) && scores.at(pos) <= score) {
        return;
    }

    scores[pos] = score;
    visited[pos] = true;
    int32_t next_score = score + 1;
    Cell *cell = maze->cell_at(position.x, position.y);

    Direction directions[] = {Direction::NORTH, Direction::EAST, Direction::SOUTH, Direction::WEST};
    for (auto direction : directions) {
        if (cell->open(direction)) {
            blit::Point next_position = blit::Point(
                    position.x + vector_x(direction),
                    position.y + vector_y(direction));
            distance(maze, next_position, next_score, scores, visited);
        }
    }
}

Distances Distances::calculate_distances(Maze *maze, blit::Point start_point) {
    std::vector<int32_t> scores(maze->width() * maze->height(), maze->width() * maze->height());
    std::vector<bool> visited(maze->width() * maze->height(), false);
    distance(maze, start_point, 0, scores, visited);
    return Distances(maze->width(), maze->height(), scores);
}

blit::Point Distances::maxPoint() {
    int max_distance = 0;
    int max_x = 0;
    int max_y = 0;
    for (int y = 0; y < height(); y++) {
        for (int x = 0; x < width(); x++) {
            int distance = distanceAt(x, y);
            if (distance > max_distance) {
                max_x = x;
                max_y = y;
                max_distance = distance;
            }
        }
    }
    return blit::Point(max_x, max_y);
}






