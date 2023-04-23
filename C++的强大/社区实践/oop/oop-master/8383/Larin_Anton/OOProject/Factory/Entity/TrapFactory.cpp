//
// Created by anton on 5/28/20.
//

#include "TrapFactory.h"

#include "../../GameObject/Entity/TrapEntity.h"

TrapFactory::TrapFactory(int dmgAmount) : trapDmg(dmgAmount) {}

std::shared_ptr<GameObject> TrapFactory::createObject(int x, int y, Devotion devotion) {
    new TrapEntity(x,y,devotion,trapDmg);
    auto rPtr = std::make_shared<TrapEntity>(x,y,devotion,trapDmg);
    return std::static_pointer_cast<GameObject>(rPtr);
}
