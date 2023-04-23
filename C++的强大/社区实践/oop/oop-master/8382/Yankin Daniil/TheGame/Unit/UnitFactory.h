#pragma once

#include "Unit.h"


class UnitFactory {
public:
    Unit* produce(uint16_t unitType, Point point, Base* base);
    Unit* produce(Unit::UnitSnapshot& snapshot, Base* base);
    Unit* produce(Unit::UnitSnapshot& snapshot, UnitGroup* group);
};
