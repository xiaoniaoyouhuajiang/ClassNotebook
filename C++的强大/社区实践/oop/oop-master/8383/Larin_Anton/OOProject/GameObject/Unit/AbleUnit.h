//
// Created by anton on 5/23/20.
//

#ifndef OOPROJECT_ABLEUNIT_H
#define OOPROJECT_ABLEUNIT_H

#include "Unit.h"

class AbleUnit:public Unit {
public:
    AbleUnit(int x, int y, Devotion devotion, CommonClass objectClass, int health, int armour, float dmgmul,
             int abPower, int abRange, int mbAgility, int mbRange);

};


#endif //OOPROJECT_ABLEUNIT_H
