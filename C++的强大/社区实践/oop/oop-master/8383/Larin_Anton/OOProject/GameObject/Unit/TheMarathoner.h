//
// Created by anton on 5/24/20.
//

#ifndef OOPROJECT_THEMARATHONER_H
#define OOPROJECT_THEMARATHONER_H

#include "MobileUnit.h"

class TheMarathoner:public MobileUnit {
public:
    TheMarathoner(int x, int y, Devotion devotion, int health, int armour, float dmgmul, int abPower,
                  int abRange, int mbAgility, int mbRange);

protected:
    CommonClass getObjectClass() override;

};


#endif //OOPROJECT_THEMARATHONER_H
