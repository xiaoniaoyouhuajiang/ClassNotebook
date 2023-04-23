#pragma once

#include "strategies/istrategy.h"

class HealthDecrease : public IStrategy
{
public:
    virtual ~HealthDecrease();
    virtual void interact(Unit* unit) override;
};

