//
// Created by anton on 5/28/20.
//

#include "BlockEntity.h"

#include "../Unit/Unit.h"

BlockEntity::BlockEntity(int x, int y, Devotion devotion, int health)
        : Entity(x, y, devotion, CommonClass ::BlockEntity, health, EntityType::BlockEntity) {}

void BlockEntity::react(std::shared_ptr<GameObject> sbj) {

}

void BlockEntity::restep(std::shared_ptr<GameObject> sbj) {
    std::shared_ptr<Unit> ptr = std::dynamic_pointer_cast<Unit>(sbj);
    if(ptr)ptr->setBlocked(true);
}

CommonClass BlockEntity::getObjectClass() {
    return CommonClass ::BlockEntity;
}
