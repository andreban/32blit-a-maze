//
// Created by andre on 08/06/2021.
//

#include "GameOver.h"
#include "32blit.hpp"

using namespace blit;

void GameOver::update(uint32_t time) {
    if (buttons.pressed & A) {
        mDone = true;
    }
}

void GameOver::render(uint32_t time) {
    screen.alpha = 255;
    screen.mask = nullptr;
    screen.pen = Pen(255, 255, 255);
    screen.rectangle(Rect(0, 0, 320, 14));
    screen.pen = Pen(0, 0, 0);
    screen.text("Game Over.", minimal_font, Point(5, 4));
}

bool GameOver::done() {
    return mDone;
}

void GameOver::reset() {
    mDone = false;
}
