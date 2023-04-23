
#pragma once

#include "strategies/istrategy.h"

class MovementRadiusIncrease : public IStrategy
{
public:
    virtual ~MovementRadiusIncrease();
    virtual void interact(Unit* unit) override;
};

