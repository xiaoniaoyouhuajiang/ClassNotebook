//
// Created by anton on 5/23/20.
//

#include "AbleUnit.h"

AbleUnit::AbleUnit(int x, int y, Devotion devotion, CommonClass objectClass, int health, int armour, float dmgmul,
                   int abPower, int abRange, int mbAgility, int mbRange) : Unit(x, y, devotion,
                                                                                                    objectClass, health,
                                                                                                    armour, dmgmul,
                                                                                                    abPower, abRange,
                                                                                                    mbAgility, mbRange,
                                                                                                    UnitType::AbleUnit) {}
