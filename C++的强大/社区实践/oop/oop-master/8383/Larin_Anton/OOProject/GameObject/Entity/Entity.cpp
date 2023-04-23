//
// Created by anton on 5/10/20.
//

#include "Entity.h"

void Entity::act(std::shared_ptr<GameObject> obj) {

}

void Entity::step(std::shared_ptr<GameObject> obj) {

}

bool Entity::canStep(int x, int y) {
    return false;
}

bool Entity::canAct(int x, int y) {
    return false;
}

Entity::Entity(int x, int y, Devotion devotion, CommonClass objectClass, int health, EntityType entityType)
        : GameObject(x, y, false, devotion,
                     ObjectType ::Entity, objectClass,
                     health, 0, 1),
          entityType(entityType) {}
