#pragma once

#include "UnitUnitHandler.h"
#include "UnitBaseHandler.h"
#include "UnitLandscapeHandler.h"

class Object;
class IUnit;


class UnitActionHandler
{
public:
    void handle(IUnit* unit, Object* passive);
};
