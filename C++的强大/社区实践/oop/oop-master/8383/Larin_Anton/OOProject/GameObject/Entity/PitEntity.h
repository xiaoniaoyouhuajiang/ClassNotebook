//
// Created by anton on 5/28/20.
//

#ifndef OOPROJECT_PITENTITY_H
#define OOPROJECT_PITENTITY_H

#include "Entity.h"

class PitEntity: public Entity{
public:
    PitEntity(int x, int y, Devotion devotion, int health, int dmgAmount);

    void react(std::shared_ptr<GameObject> sbj) override;

    void restep(std::shared_ptr<GameObject> sbj) override;

    CommonClass getObjectClass() override;

private:
    int dmgAmount;

};


#endif //OOPROJECT_PITENTITY_H
