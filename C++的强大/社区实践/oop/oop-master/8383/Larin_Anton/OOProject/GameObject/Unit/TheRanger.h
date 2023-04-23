//
// Created by anton on 5/23/20.
//

#ifndef OOPROJECT_THERANGER_H
#define OOPROJECT_THERANGER_H

#include "AbleUnit.h"

class TheRanger:public AbleUnit{
public:
    TheRanger(int x, int y, Devotion devotion, int health, int armour, float dmgmul, int abPower,
              int abRange, int mbAgility, int mbRange);

private:
    CommonClass getObjectClass() override;

    //int rangeMultiplyer;


};


#endif //OOPROJECT_THERANGER_H
