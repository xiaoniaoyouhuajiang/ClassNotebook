//
// Created by Alex on 21.03.2020.
//

#ifndef GAME_ARCHER_H
#define GAME_ARCHER_H


#include "RangedUnit.h"

class Archer : public RangedUnit{
public:
    Archer(int startX, int startY, Weapon *unitWeapon, Armor *unitArmor);
    void attack(Unit *unit) override ;
};


#endif //GAME_ARCHER_H
