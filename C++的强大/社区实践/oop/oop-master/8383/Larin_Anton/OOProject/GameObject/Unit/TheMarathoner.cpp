//
// Created by anton on 5/24/20.
//

#include "TheMarathoner.h"

TheMarathoner::TheMarathoner(int x, int y, Devotion devotion, int health, int armour, float dmgmul, int abPower,
                             int abRange, int mbAgility, int mbRange) : MobileUnit(x, y,
                                                                                                              devotion,
                                                                                                              CommonClass::TheMarathoner,
                                                                                                              health,
                                                                                                              armour,
                                                                                                              dmgmul,
                                                                                                              abPower,
                                                                                                              abRange,
                                                                                                              mbAgility,
                                                                                                              mbRange) {}

CommonClass TheMarathoner::getObjectClass() {
    return CommonClass::TheMarathoner;
}
