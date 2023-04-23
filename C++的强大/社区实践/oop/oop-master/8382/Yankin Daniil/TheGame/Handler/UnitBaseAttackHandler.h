#pragma once

#include "RouteHandler.h"

class IUnit;
class Base;


class UnitBaseAttackHandler
{
public:
    void handle(IUnit* attacker, Base* base);
};
