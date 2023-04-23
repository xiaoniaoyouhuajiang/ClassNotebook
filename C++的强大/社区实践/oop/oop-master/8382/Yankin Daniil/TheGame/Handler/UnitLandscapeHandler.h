#pragma once

#include "RouteHandler.h"

class ILandscape;
class IUnit;


class UnitLandscapeHandler
{
public:
    void handle(IUnit* unit, ILandscape* land);
};
