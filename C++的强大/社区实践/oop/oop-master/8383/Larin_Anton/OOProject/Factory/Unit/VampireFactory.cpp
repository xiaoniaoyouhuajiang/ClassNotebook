//
// Created by anton on 5/25/20.
//

#include "VampireFactory.h"

#include "../../GameObject/Unit/TheVampire.h"

VampireFactory::VampireFactory(int health, int armour, float dmgmul, int abPower, int abRange, int mbAgility,
                               int mbRange, float vampiricMultiplyer) : AbstractUnitFactory(health, armour, dmgmul,
                                                                                            abPower, abRange, mbAgility,
                                                                                            mbRange),
                                                                        vampiricMultiplyer(vampiricMultiplyer) {}

std::shared_ptr<GameObject> VampireFactory::createObject(int x, int y, Devotion devotion) {
    auto rPtr = std::make_shared<TheVampire>(x,y,devotion,health,armour,dmgmul,abPower,abRange,mbAgility,mbRange,vampiricMultiplyer);
    onUnitCreate(std::static_pointer_cast<Unit>(rPtr));
    return std::static_pointer_cast<GameObject>(rPtr);
}
