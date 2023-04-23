//
// Created by anton on 5/28/20.
//

#include "TrapEntity.h"

TrapEntity::TrapEntity(int x, int y, Devotion devotion, int dmgAmount) : Entity(x, y, devotion, CommonClass ::TrapEntity, 1, EntityType::TrapEntity), dmgAmount(dmgAmount) {}

void TrapEntity::react(std::shared_ptr<GameObject> sbj) {
    sbj->getVitality().damage(dmgAmount);
    setToBeRemoved(true);
}

void TrapEntity::restep(std::shared_ptr<GameObject> sbj) {
    sbj->getVitality().damage(dmgAmount);
    setToBeRemoved(true);
}

CommonClass TrapEntity::getObjectClass() {
    return CommonClass::TrapEntity;
}
