#pragma once

#include "strategies/istrategy.h"

class AttackRadiusIncrease : public IStrategy
{
public:
    virtual ~AttackRadiusIncrease();
    virtual void interact(Unit* unit) override;
};

