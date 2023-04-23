#pragma once

#include "strategies/istrategy.h"

class HealthIncrease : public IStrategy
{
public:
    virtual ~HealthIncrease();
    virtual void interact(Unit* unit) override;
};

