//
// Created by anton on 5/24/20.
//

#ifndef OOPROJECT_THEPOWERFUL_H
#define OOPROJECT_THEPOWERFUL_H

#include "AbleUnit.h"

class ThePowerful:public AbleUnit {
public:
    ThePowerful(int x, int y, Devotion devotion, int health, int armour, float dmgmul, int abPower,
                int abRange, int mbAgility, int mbRange);

    CommonClass getObjectClass() override;


};


#endif //OOPROJECT_THEPOWERFUL_H
