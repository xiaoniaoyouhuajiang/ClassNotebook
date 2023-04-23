#pragma once
#include <iostream>
#include "game.h"
#include "objects/object.h"
#include "command/command.h"
#include "command/addunit.h"
#include "command/attackunit.h"
#include "command/moveunit.h"
#include "command/moveunittoneutral.h"


class Handler
{
public:
    virtual Handler *SetNext(Handler *handler) = 0;
    virtual Base* Add(Base* object) = 0;
    virtual bool Attack(Unit* who, Object* whom) = 0;
    virtual bool Move(Unit* who, int x2, int y2) = 0;
    virtual bool MoveToNeutr(Unit* unit, NeutralObject* obj) = 0;

};

