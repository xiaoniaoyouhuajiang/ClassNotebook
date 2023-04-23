//
// Created by anton on 5/25/20.
//

#include "PowerfulFactory.h"

#include "../../GameObject/Unit/ThePowerful.h"

PowerfulFactory::PowerfulFactory(int health, int armour, float dmgmul, int abPower, int abRange, int mbAgility,
                                 int mbRange, int enhancedPower) : AbstractUnitFactory(health, armour, dmgmul, abPower,
                                                                                       abRange, mbAgility, mbRange),
                                                                   enhancedPower(enhancedPower) {}

std::shared_ptr<GameObject> PowerfulFactory::createObject(int x, int y, Devotion devotion) {
    auto rPtr = std::make_shared<ThePowerful>(x,y,devotion,health,armour,dmgmul,enhancedPower,abRange,mbAgility,mbRange);
    onUnitCreate(std::static_pointer_cast<Unit>(rPtr));
    return std::static_pointer_cast<GameObject>(rPtr);
}
