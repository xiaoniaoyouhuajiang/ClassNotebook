//
// Created by Alex on 21.03.2020.
//

#ifndef GAME_ATTACKINFANTRY_H
#define GAME_ATTACKINFANTRY_H


#include "../Unit.h"

class AttackInfantry: public Unit {
public:
    AttackInfantry(int startX, int startY, Weapon *unitWeapon, Armor *unitArmor);

    AttackInfantry();
};


#endif //GAME_ATTACKINFANTRY_H
