#pragma once

#include "UnitUnitAttackHandler.h"
#include "UnitUnitUnionHandler.h"

class IUnit;


class UnitUnitHandler
{
public:
    void handle(IUnit* active, IUnit* passive);
};
