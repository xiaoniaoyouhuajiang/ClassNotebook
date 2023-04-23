#pragma once

#include "strategies/istrategy.h"

class Kill : public IStrategy
{
public:
    virtual ~Kill();
    virtual void interact(Unit* unit) override;
};

