//
// Created by andre on 08/06/2021.
//

#ifndef AMAZE_GAMEOVER_H
#define AMAZE_GAMEOVER_H


#include <cstdint>

class GameOver {
public:
    void update(uint32_t time);
    void render(uint32_t time);
};


#endif //AMAZE_GAMEOVER_H