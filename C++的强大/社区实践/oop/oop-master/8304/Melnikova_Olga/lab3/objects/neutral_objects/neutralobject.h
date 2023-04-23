#pragma once

#include "objects/object.h"
//#include "strategies/istrategy.h"
class IStrategy;

class NeutralObject : public Object //наследуемся от IStrategy
{
public:
    virtual ~NeutralObject();
    IStrategy* action;
    bool isHorse;
    bool isMedicine;
    bool isPower;
    bool isShield;
};

