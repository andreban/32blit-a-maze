//
// Created by andre on 08/06/2021.
//

#ifndef AMAZE_MAINMENU_H
#define AMAZE_MAINMENU_H

#include <cstdint>

class MainMenu {
private:
    bool newGame_ = false;
public:
    void update(uint32_t time);
    void render(uint32_t time);
    void reset();
    bool newGame();
};

#endif //AMAZE_MAINMENU_H
