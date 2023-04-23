//
// Created by anton on 5/24/20.
//

#ifndef OOPROJECT_THEVAMPIRE_H
#define OOPROJECT_THEVAMPIRE_H

#include "EnduringUnit.h"

class TheVampire:public EnduringUnit {
public:
    TheVampire(int x, int y, Devotion devotion, int health, int armour, float dmgmul, int abPower, int abRange,
               int mbAgility, int mbRange, float vampiricMultiplyer);

    void act(std::shared_ptr<GameObject> obj) override;

protected:
    float vampiricMultiplyer;

    CommonClass getObjectClass() override;


};


#endif //OOPROJECT_THEVAMPIRE_H
