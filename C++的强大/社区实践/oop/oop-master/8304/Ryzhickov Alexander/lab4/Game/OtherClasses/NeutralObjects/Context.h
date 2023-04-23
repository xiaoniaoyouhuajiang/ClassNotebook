//
// Created by Alex on 12.04.2020.
//

#ifndef GAME_CONTEXT_H
#define GAME_CONTEXT_H

#include "NeutralObject.h"
#include "../../Units/Unit.h"

class Context
{
protected:
    NeutralObject* neutralObject;

public:
    virtual ~Context() {}
    virtual void useStrategy(Unit *unit) = 0;
    virtual void setStrategy(NeutralObject* v) = 0;
};
#endif //GAME_CONTEXT_H
