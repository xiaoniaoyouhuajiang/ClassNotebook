//
// Created by anton on 5/28/20.
//

#include "PitEntity.h"

PitEntity::PitEntity(int x, int y, Devotion devotion, int health, int dmgAmount) : Entity(x, y, devotion, CommonClass ::PitEntity, health, EntityType::PitEntity), dmgAmount(dmgAmount) {}

void PitEntity::react(std::shared_ptr<GameObject> sbj) {

}

void PitEntity::restep(std::shared_ptr<GameObject> sbj) {
    sbj->setToBeRemoved(true);
}

CommonClass PitEntity::getObjectClass() {
    return CommonClass ::PitEntity;
}
