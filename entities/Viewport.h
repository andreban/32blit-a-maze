//
// Created by andre on 07/06/2021.
//

#ifndef AMAZE_VIEWPORT_H
#define AMAZE_VIEWPORT_H

#include <types/size.hpp>
#include <types/rect.hpp>

class Viewport {
private:
    blit::Size mScreenSize;
    blit::Size mMapSize;
    blit::Rect mViewport;
public:
    Viewport(blit::Size screen_size, blit::Size map_size);
    void update(blit::Point center);
    blit::Rect translate(blit::Rect rect);
};

#endif //AMAZE_VIEWPORT_H
