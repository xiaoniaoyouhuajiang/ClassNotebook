//
// Created by anton on 5/28/20.
//

#include "HealFactory.h"

#include "../../GameObject/Entity/HealEntity.h"

HealFactory::HealFactory(int healAmount) : healAmount(healAmount) {}

std::shared_ptr<GameObject> HealFactory::createObject(int x, int y, Devotion devotion) {
    auto rPtr = std::make_shared<HealEntity>(x,y,devotion,healAmount);
    return std::static_pointer_cast<GameObject>(rPtr);
}
