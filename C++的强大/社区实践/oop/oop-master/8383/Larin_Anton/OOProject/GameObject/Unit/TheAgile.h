//
// Created by anton on 5/24/20.
//

#ifndef OOPROJECT_THEAGILE_H
#define OOPROJECT_THEAGILE_H

#include "MobileUnit.h"

class TheAgile:public MobileUnit{
public:
    TheAgile(int x, int y, Devotion devotion, int health, int armour, float dmgmul, int abPower, int abRange,
             int mbAgility, int mbRange);

protected:
    CommonClass getObjectClass() override;


};


#endif //OOPROJECT_THEAGILE_H
