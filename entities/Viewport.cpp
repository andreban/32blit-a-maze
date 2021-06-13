//
// Created by andre on 07/06/2021.
//

#include "Viewport.h"

Viewport::Viewport(blit::Size screen_size, blit::Size map_size): mScreenSize(screen_size), mMapSize(map_size) {
    update(blit::Point());
}

void Viewport::update(blit::Point center) {
    mViewport = blit::Rect(
            std::min(mMapSize.w - mScreenSize.w, std::max(center.x - mScreenSize.w / 2, (int32_t)0)),
            std::min(mMapSize.h - mScreenSize.h, std::max(center.y - mScreenSize.h / 2, (int32_t)0)),
            mScreenSize.w,
            mScreenSize.h
    );
}

blit::Rect Viewport::translate(blit::Rect rect) {
    return blit::Rect(
            rect.x - mViewport.x,
            rect.y - mViewport.y,
            rect.w,
            rect.h
    );
}

