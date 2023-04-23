//
// Created by anton on 5/25/20.
//

#ifndef OOPROJECT_POWERFULFACTORY_H
#define OOPROJECT_POWERFULFACTORY_H

#include "AbstractUnitFactory.h"

class PowerfulFactory:public AbstractUnitFactory {
public:
    PowerfulFactory(int health, int armour, float dmgmul, int abPower, int abRange, int mbAgility, int mbRange,
                    int enhancedPower);

    std::shared_ptr<GameObject> createObject(int x, int y, Devotion devotion) override;

private:
    int enhancedPower;
};


#endif //OOPROJECT_POWERFULFACTORY_H
