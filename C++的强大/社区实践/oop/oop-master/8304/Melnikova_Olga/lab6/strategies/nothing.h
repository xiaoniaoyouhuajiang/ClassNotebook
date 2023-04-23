#pragma once

#include "strategies/istrategy.h"

class Nothing : public IStrategy
{
public:
    virtual ~Nothing();
    virtual void interact(Unit* unit) override;
};
