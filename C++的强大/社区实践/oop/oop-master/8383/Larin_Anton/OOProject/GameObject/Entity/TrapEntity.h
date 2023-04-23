//
// Created by anton on 5/28/20.
//

#ifndef OOPROJECT_TRAPENTITY_H
#define OOPROJECT_TRAPENTITY_H

#include "Entity.h"

class TrapEntity: public Entity {
public:
    TrapEntity(int x, int y, Devotion devotion, int dmgAmount);

private:
    void react(std::shared_ptr<GameObject> sbj) override;

    void restep(std::shared_ptr<GameObject> sbj) override;

    CommonClass getObjectClass() override;

private:
    int dmgAmount;

};


#endif //OOPROJECT_TRAPENTITY_H
