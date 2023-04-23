//
// Created by anton on 5/24/20.
//

#include "TheAgile.h"

TheAgile::TheAgile(int x, int y, Devotion devotion, int health, int armour, float dmgmul, int abPower, int abRange,
                   int mbAgility, int mbRange) : MobileUnit(x, y, devotion, CommonClass::TheAgile,
                                                                                      health, armour, dmgmul, abPower,
                                                                                      abRange, mbAgility, mbRange) {}

CommonClass TheAgile::getObjectClass() {
    return CommonClass::TheAgile;
}
