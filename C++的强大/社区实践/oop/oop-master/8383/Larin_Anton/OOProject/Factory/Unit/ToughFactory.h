//
// Created by anton on 5/26/20.
//

#ifndef OOPROJECT_TOUGHFACTORY_H
#define OOPROJECT_TOUGHFACTORY_H

#include "AbstractUnitFactory.h"

class ToughFactory: public AbstractUnitFactory {
public:
    ToughFactory(int health, int armour, float dmgmul, int abPower, int abRange, int mbAgility, int mbRange,
                 int enhancedHealth);

    std::shared_ptr<GameObject> createObject(int x, int y, Devotion devotion) override;

private:
    int enhancedHealth;
};


#endif //OOPROJECT_TOUGHFACTORY_H
