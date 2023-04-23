#pragma once

#include "objects/units/unit.h"
//class Unit;

class IStrategy  //интерфейс какой-то стратегии (зав. от юнита)
{
public:
    virtual void interact(Unit* unit) = 0;
    virtual ~IStrategy();
    
};
