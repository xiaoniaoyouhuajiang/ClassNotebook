#pragma once

#include "RouteHandler.h"

class IUnit;
class Object;


class UnitUnitAttackHandler
{
public:
    void handle(IUnit* attacker, IUnit* defender);
};
