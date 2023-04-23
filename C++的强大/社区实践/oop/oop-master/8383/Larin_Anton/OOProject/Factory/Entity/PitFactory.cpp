//
// Created by anton on 5/28/20.
//

#include "PitFactory.h"

#include "../../GameObject/Entity/PitEntity.h"


std::shared_ptr<GameObject> PitFactory::createObject(int x, int y, Devotion devotion) {
    auto rPtr = std::make_shared<PitEntity>(x,y,devotion,pitHealth,pitDmg);
    return std::static_pointer_cast<GameObject>(rPtr);
}

PitFactory::PitFactory(int pitHealth, int dmgAmount) : pitHealth(pitHealth), pitDmg(dmgAmount) {}
