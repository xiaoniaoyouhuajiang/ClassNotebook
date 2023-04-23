//
// Created by Alex on 21.03.2020.
//

#ifndef GAME_RANGEDUNIT_H
#define GAME_RANGEDUNIT_H


#include "../Unit.h"

class RangedUnit : public Unit {
protected:
    unsigned countShots;
public:
    RangedUnit(int startX, int startY, Weapon *unitWeapon, Armor *unitArmor);
    RangedUnit();
};


#endif //GAME_RANGEDUNIT_H
