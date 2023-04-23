#pragma once

#include "strategies/istrategy.h"

class EnableShield : public IStrategy
{
public:
    virtual ~EnableShield();
    virtual void interact(Unit* unit) override;
};

