//
// Created by Mila
//

#ifndef UNTITLED_CONTEXT_H
#define UNTITLED_CONTEXT_H


#include "../Units/Unit.h"
#include "NeutralObjectInterface.h"

class Context{
protected:
    NeutralObjectInterface* neutralObject;

public:
    virtual void useStrategy(Unit* unit) = 0;
    virtual void setStrategy(NeutralObjectInterface* neutralObject) = 0;
};

#endif //UNTITLED_CONTEXT_H
