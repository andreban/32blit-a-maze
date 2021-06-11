//
// Created by andre on 08/06/2021.
//

#ifndef AMAZE_DISTANCES_H
#define AMAZE_DISTANCES_H


#include <cstdint>
#include <vector>
#include <types/point.hpp>
#include "Maze.h"

class Distances {
private:
    int32_t width_;
    int32_t height_;
    std::vector<int32_t> distances;
public:
    Distances(int32_t width, int32_t height, std::vector<int32_t> distances);
    int32_t width();
    int32_t height();
    int32_t max();
    int32_t distanceAt(int32_t x, int32_t y);
    blit::Point maxPoint();
    static Distances calculate_distances(Maze *maze, blit::Point start_point);
};

#endif //AMAZE_DISTANCES_H
