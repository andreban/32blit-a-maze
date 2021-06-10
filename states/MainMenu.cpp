//
// Created by andre on 08/06/2021.
//

#include "MainMenu.h"
#include "32blit.hpp"

using namespace blit;

void MainMenu::update(uint32_t time) {
    if (pressed(A)) {
        newGame_ = true;
    }
}

void MainMenu::render(uint32_t time) {
    screen.clear();

    // draw some text at the top of the screen
    screen.alpha = 255;
    screen.mask = nullptr;
    screen.pen = Pen(255, 255, 255);
    screen.rectangle(Rect(0, 0, 320, 14));
    screen.pen = Pen(0, 0, 0);
    screen.text("Press A to start.", minimal_font, Point(5, 4));
}

void MainMenu::reset() {
    newGame_ = false;
}

bool MainMenu::newGame() {
    return newGame_;
}
