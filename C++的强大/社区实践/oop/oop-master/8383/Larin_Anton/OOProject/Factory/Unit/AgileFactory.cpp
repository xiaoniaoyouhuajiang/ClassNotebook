//
// Created by anton on 5/25/20.
//

#include "AgileFactory.h"

#include "../../GameObject/Unit/TheAgile.h"

AgileFactory::AgileFactory(int health, int armour, float dmgmul, int abPower, int abRange, int mbAgility, int mbRange,
                           int enhancedAgility) : AbstractUnitFactory(health, armour, dmgmul, abPower, abRange,
                                                                      mbAgility, mbRange),
                                                  enhancedAgility(enhancedAgility) {}

std::shared_ptr<GameObject> AgileFactory::createObject(int x, int y, Devotion devotion) {
    auto rPtr = std::make_shared<TheAgile>(x,y,devotion,health,armour,dmgmul,abPower,abRange,enhancedAgility,mbRange);
    onUnitCreate(std::static_pointer_cast<Unit>(rPtr));
    return std::static_pointer_cast<GameObject>(rPtr);
}
