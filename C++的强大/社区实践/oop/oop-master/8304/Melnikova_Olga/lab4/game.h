#pragma once

#include "field/field.h"
#include "objects/base.h"
#include "objects/object.h"
#include "fabrics/objectFabric.h"

#include "fabrics/landscapefabric.h"
#include "landscapes/cliffProxy.h"
#include "landscapes/gladeProxy.h"
#include "landscapes/swampProxy.h"

#include "strategies/istrategy.h"


class Game
{
public:
    Game();
    Game(int h, int w);
    ~Game();

    Field* field;
    Base *base1;
    Base *base2;

    Landscape* cliff;
    Landscape* glade;
    Landscape* swamp;

    bool isActionDone;
    int isAttackDone;

    void atack(Unit* unit1, Object* unit2);
    bool move(int x1, int y1, int x2, int y2);
    bool moveToNeutral(Unit* unit, NeutralObject* obj);
    bool add(std::string who, bool numBase, int x, int y);
    void del(Unit* unit);

};
