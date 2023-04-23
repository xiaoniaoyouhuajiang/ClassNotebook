#pragma once

#include "objects/object.h"
//#include "strategies/istrategy.h"
class IStrategy;

class NeutralObject : public Object
{
public:
    //NeutralObject();
    virtual ~NeutralObject();

    IStrategy* action;

    //int damage;
    // + интерфейс
};

