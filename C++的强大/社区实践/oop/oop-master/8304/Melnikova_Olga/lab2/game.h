#pragma once

#include "field/field.h"
#include "objects/base.h"
#include "objects/object.h"
#include "fabrics/objectFabric.h"

#include "fabrics/landscapefabric.h"
#include "landscapes/cliffProxy.h"
#include "landscapes/gladeProxy.h"
#include "landscapes/swampProxy.h"


class Game
{
public:
    Game(int h, int w);
    ~Game();

    Field* field;
    Base *base1;
    Base *base2;

    Landscape* cliff;
    Landscape* glade;
    Landscape* swamp;

    // Unit** units;


};
