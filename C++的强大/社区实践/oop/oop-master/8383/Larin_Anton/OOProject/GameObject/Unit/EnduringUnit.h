//
// Created by anton on 5/24/20.
//

#ifndef OOPROJECT_ENDURINGUNIT_H
#define OOPROJECT_ENDURINGUNIT_H

#include "Unit.h"

class EnduringUnit:public Unit {
public:
    EnduringUnit(int x, int y, Devotion devotion, CommonClass objectClass, int health, int armour,
                 float dmgmul, int abPower, int abRange, int mbAgility, int mbRange);


};


#endif //OOPROJECT_ENDURINGUNIT_H
