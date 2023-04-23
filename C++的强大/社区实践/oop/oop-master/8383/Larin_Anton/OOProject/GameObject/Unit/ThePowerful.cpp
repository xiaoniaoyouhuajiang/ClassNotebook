//
// Created by anton on 5/24/20.
//

#include "ThePowerful.h"

ThePowerful::ThePowerful(int x, int y, Devotion devotion, int health, int armour, float dmgmul, int abPower,
                         int abRange, int mbAgility, int mbRange) : AbleUnit(x, y, devotion, CommonClass::ThePowerful,
                                                                                          health, armour, dmgmul,
                                                                                          abPower, abRange, mbAgility,
                                                                                          mbRange) {}

CommonClass ThePowerful::getObjectClass() {
    return CommonClass::ThePowerful;
}
