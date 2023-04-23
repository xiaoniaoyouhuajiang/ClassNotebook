//
// Created by anton on 5/24/20.
//

#ifndef OOPROJECT_THETOUGH_H
#define OOPROJECT_THETOUGH_H

#include "EnduringUnit.h"

class TheTough:public EnduringUnit {
public:
    TheTough(int x, int y, Devotion devotion, int health, int armour, float dmgmul, int abPower, int abRange,
             int mbAgility, int mbRange);

    void react(std::shared_ptr<GameObject> sbj) override;

protected:
    CommonClass getObjectClass() override;

};


#endif //OOPROJECT_THETOUGH_H
