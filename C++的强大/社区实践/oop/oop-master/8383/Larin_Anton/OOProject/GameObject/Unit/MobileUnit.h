//
// Created by anton on 5/24/20.
//

#ifndef OOPROJECT_MOBILEUNIT_H
#define OOPROJECT_MOBILEUNIT_H

#include "Unit.h"

class MobileUnit:public Unit {
public:
    MobileUnit(int x, int y, Devotion devotion, CommonClass objectClass, int health, int armour,
               float dmgmul, int abPower, int abRange, int mbAgility, int mbRange);


};


#endif //OOPROJECT_MOBILEUNIT_H
