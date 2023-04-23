//
// Created by Alex on 21.03.2020.
//

#ifndef GAME_KNIGHT_H
#define GAME_KNIGHT_H


#include "HeavyInfantry.h"

class Knight: public HeavyInfantry {
public:
    Knight(int startX, int startY, Weapon *unitWeapon, Armor *unitArmor);
    void attack(Unit *unit) override ;
};


#endif //GAME_KNIGHT_H
