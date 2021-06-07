//
// Created by andre on 07/06/2021.
//

#include "Viewport.h"

Viewport::Viewport(blit::Size screen_size, blit::Size map_size): screen_size(screen_size), map_size(map_size) {
    update(blit::Point());
}

void Viewport::update(blit::Point center) {
    viewport = blit::Rect(
            std::min(map_size.w - screen_size.w, std::max(center.x - screen_size.w / 2, (int32_t)0)),
            std::min(map_size.h - screen_size.h, std::max(center.y - screen_size.h / 2, (int32_t)0)),
            screen_size.w,
            screen_size.h
    );
}

blit::Rect Viewport::translate(blit::Rect rect) {
    return blit::Rect(
            rect.x - viewport.x,
            rect.y - viewport.y,
            rect.w,
            rect.h
    );
}

