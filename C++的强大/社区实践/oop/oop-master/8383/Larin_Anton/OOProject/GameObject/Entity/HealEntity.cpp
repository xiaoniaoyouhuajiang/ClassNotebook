//
// Created by anton on 5/28/20.
//

#include "HealEntity.h"

HealEntity::HealEntity(int x, int y, Devotion devotion, int healAmount) : Entity(x, y, devotion, CommonClass::HealEntity , 1, EntityType::HealEntity),
                                                                          healAmount(healAmount) {}

void HealEntity::react(std::shared_ptr<GameObject> sbj) {
    sbj->getVitality().heal(healAmount);
    setToBeRemoved(true);
}

void HealEntity::restep(std::shared_ptr<GameObject> sbj) {
    sbj->getVitality().heal(healAmount);
    setToBeRemoved(true);
}

CommonClass HealEntity::getObjectClass() {
    return CommonClass::HealEntity;
}
