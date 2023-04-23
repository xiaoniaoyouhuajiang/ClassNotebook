//
// Created by anton on 5/25/20.
//

#ifndef OOPROJECT_AGILEFACTORY_H
#define OOPROJECT_AGILEFACTORY_H

#include "AbstractUnitFactory.h"

class AgileFactory:public AbstractUnitFactory {
public:
    AgileFactory(int health, int armour, float dmgmul, int abPower, int abRange, int mbAgility, int mbRange,
                 int enhancedAgility);

    std::shared_ptr<GameObject> createObject(int x, int y, Devotion devotion) override;


private:
    int enhancedAgility;
};


#endif //OOPROJECT_AGILEFACTORY_H
