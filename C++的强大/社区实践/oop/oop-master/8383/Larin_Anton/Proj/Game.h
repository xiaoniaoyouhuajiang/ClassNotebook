//
// Created by anton on 2/11/20.
//

#ifndef PROJ_GAME_H
#define PROJ_GAME_H

#include <cassert>
#include <iostream>

//#include "libs/etl/profiles/etl_profile.h"
//#include "libs/etl/vector.h"

#include "GameObject.h"
#include "Field.h"
#include "Factory/CommonFactory.h"
#include "Mediator.h"

#define FIELD_ABS_MAX 8

class Game {
private:
    Mediator *mediator;
    Field *field;
    CommonFactory *factory;
    //etl::vector<GameObject*, FIELD_ABS_MAX*FIELD_ABS_MAX> objVector;

public:
    Game(int fieldWidth, int fieldHeight);

    void run();

    virtual ~Game();
};


#endif //PROJ_GAME_H
