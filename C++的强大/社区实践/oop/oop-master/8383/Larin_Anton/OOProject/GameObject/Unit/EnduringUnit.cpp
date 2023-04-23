//
// Created by anton on 5/24/20.
//

#include "EnduringUnit.h"

EnduringUnit::EnduringUnit(int x, int y, Devotion devotion, CommonClass objectClass, int health, int armour,
                           float dmgmul, int abPower, int abRange, int mbAgility, int mbRange)
        : Unit(x, y, devotion, objectClass, health, armour, dmgmul, abPower, abRange, mbAgility, mbRange, UnitType::EnduringUnit) {}
