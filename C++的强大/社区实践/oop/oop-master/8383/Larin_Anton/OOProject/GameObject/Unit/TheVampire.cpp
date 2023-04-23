//
// Created by anton on 5/24/20.
//

#include "TheVampire.h"

TheVampire::TheVampire(int x, int y, Devotion devotion, int health, int armour, float dmgmul, int abPower, int abRange,
                       int mbAgility, int mbRange, float vampiricMultiplyer) : EnduringUnit(x, y, devotion, CommonClass::TheVampire,
                                                                                            health, armour, dmgmul,
                                                                                            abPower, abRange, mbAgility,
                                                                                            mbRange),vampiricMultiplyer(vampiricMultiplyer) {}

CommonClass TheVampire::getObjectClass() {
    return CommonClass::TheVampire;
}

void TheVampire::act(std::shared_ptr<GameObject> obj) {
    Unit::act(obj);
    std::shared_ptr<Unit> unit = std::dynamic_pointer_cast<Unit>(obj);
    if(unit){
        getVitality().heal(getAbility().power*vampiricMultiplyer);//Heal self by own power
    }
}
