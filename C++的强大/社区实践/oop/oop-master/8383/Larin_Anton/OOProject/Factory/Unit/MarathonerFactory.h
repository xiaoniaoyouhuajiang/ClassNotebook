//
// Created by anton on 5/25/20.
//

#ifndef OOPROJECT_MARATHONERFACTORY_H
#define OOPROJECT_MARATHONERFACTORY_H

#include "AbstractUnitFactory.h"

class MarathonerFactory:public AbstractUnitFactory {
public:
    MarathonerFactory(int health, int armour, float dmgmul, int abPower, int abRange, int mbAgility, int mbRange,
                      int enhancedRange);

    std::shared_ptr<GameObject> createObject(int x, int y, Devotion devotion) override;

public:


private:
    int enhancedRange;


};


#endif //OOPROJECT_MARATHONERFACTORY_H
