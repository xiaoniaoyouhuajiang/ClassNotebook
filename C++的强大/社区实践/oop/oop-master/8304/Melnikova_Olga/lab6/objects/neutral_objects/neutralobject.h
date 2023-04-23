#pragma once

#include "objects/object.h"
//#include "strategies/istrategy.h"
class IStrategy;

class NeutralObject : public Object //наследуемся от IStrategy
{
public:
    virtual ~NeutralObject();
    IStrategy* action;
    bool isHorse = false;
    bool isMedicine = false;
    bool isPower = false;
    bool isShield = false;
};

