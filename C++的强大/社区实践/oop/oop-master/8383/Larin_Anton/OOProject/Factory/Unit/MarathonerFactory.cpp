//
// Created by anton on 5/25/20.
//

#include "MarathonerFactory.h"

#include "../../GameObject/Unit/TheMarathoner.h"

MarathonerFactory::MarathonerFactory(int health, int armour, float dmgmul, int abPower, int abRange, int mbAgility,
                                     int mbRange, int enhancedRange) : AbstractUnitFactory(health, armour, dmgmul,
                                                                                           abPower, abRange, mbAgility,
                                                                                           mbRange),
                                                                       enhancedRange(enhancedRange) {}

std::shared_ptr<GameObject> MarathonerFactory::createObject(int x, int y, Devotion devotion) {
    auto rPtr = std::make_shared<TheMarathoner>(x,y,devotion,health,armour,dmgmul,abPower,abRange,mbAgility,enhancedRange);
    onUnitCreate(std::static_pointer_cast<Unit>(rPtr));
    return std::static_pointer_cast<GameObject>(rPtr);
}
