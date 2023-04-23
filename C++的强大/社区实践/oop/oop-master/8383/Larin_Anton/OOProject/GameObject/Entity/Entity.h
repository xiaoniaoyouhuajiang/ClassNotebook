//
// Created by anton on 5/10/20.
//

#ifndef OOPROJECT_ENTITY_H
#define OOPROJECT_ENTITY_H

#include "../GameObject.h"

#include "../../Stats.h"

class Entity:public GameObject {
private:
    EntityType entityType;
public:

    Entity(int x, int y, Devotion devotion, CommonClass objectClass, int health, EntityType entityType);

    void act(std::shared_ptr<GameObject> obj) override;

    void step(std::shared_ptr<GameObject> obj) override;

    bool canStep(int x, int y) override;

    bool canAct(int x, int y) override;


};


#endif //OOPROJECT_ENTITY_H
