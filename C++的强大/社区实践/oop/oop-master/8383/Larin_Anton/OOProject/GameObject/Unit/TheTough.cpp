//
// Created by anton on 5/24/20.
//

#include "TheTough.h"

TheTough::TheTough(int x, int y, Devotion devotion, int health, int armour, float dmgmul, int abPower, int abRange,
                   int mbAgility, int mbRange) : EnduringUnit(x, y, devotion, CommonClass::TheTough,
                                                                                        health, armour, dmgmul, abPower,
                                                                                        abRange, mbAgility, mbRange) {}

CommonClass TheTough::getObjectClass() {
    return CommonClass::TheTough;
}

void TheTough::react(std::shared_ptr<GameObject> sbj) {
    std::pair<int,int> c = sbj->getCoords();
    if(canAct(c.first,c.second))
        sbj->getVitality().damage(getAbility().power);
}
