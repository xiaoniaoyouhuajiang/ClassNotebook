//
// Created by Alex on 21.03.2020.
//

#ifndef GAME_HEAVYINFANTRY_H
#define GAME_HEAVYINFANTRY_H


#include "../Unit.h"

class HeavyInfantry : public Unit {
public:
    HeavyInfantry(int startX, int startY, Weapon *unitWeapon, Armor *unitArmor);
    HeavyInfantry();
};


#endif //GAME_HEAVYINFANTRY_H
