//
// Created by Alex on 03.03.2020.
//

#ifndef MYGAME_GAME_H
#define MYGAME_GAME_H


#include "../HelpersClasses/Base/Base.h"
#include "../HelpersClasses/Field.h"

class Game {
public:
    Game();
    ~Game();
private:
    Base *base;
    Field *field;
    Unit **units;
};


#endif //MYGAME_GAME_H
