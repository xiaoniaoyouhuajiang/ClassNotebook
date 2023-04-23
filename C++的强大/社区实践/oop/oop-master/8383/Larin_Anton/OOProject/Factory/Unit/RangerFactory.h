//
// Created by anton on 5/25/20.
//

#ifndef OOPROJECT_RANGERFACTORY_H
#define OOPROJECT_RANGERFACTORY_H

#include "AbstractUnitFactory.h"

class RangerFactory:public AbstractUnitFactory {
public:

    RangerFactory(int health, int armour, float dmgmul, int abPower, int abRange, int mbAgility, int mbRange,
                  int enhancedRange);

    std::shared_ptr<GameObject> createObject(int x, int y, Devotion devotion) override;

private:
    int enhancedRange = 5;



};


#endif //OOPROJECT_RANGERFACTORY_H
