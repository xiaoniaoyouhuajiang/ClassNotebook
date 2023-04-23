//
// Created by anton on 5/25/20.
//

#ifndef OOPROJECT_VAMPIREFACTORY_H
#define OOPROJECT_VAMPIREFACTORY_H

#include "AbstractUnitFactory.h"

class VampireFactory:public AbstractUnitFactory {
public:
    VampireFactory(int health, int armour, float dmgmul, int abPower, int abRange, int mbAgility, int mbRange,
                   float vampiricMultiplyer);

    std::shared_ptr<GameObject> createObject(int x, int y, Devotion devotion) override;

private:
    float vampiricMultiplyer;

};


#endif //OOPROJECT_VAMPIREFACTORY_H
