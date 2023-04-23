//
// Created by Alex on 21.03.2020.
//

#ifndef GAME_MAGICIAN_H
#define GAME_MAGICIAN_H


#include "RangedUnit.h"

class Magician : public RangedUnit {
public:
    Magician(int startX, int startY, Weapon *unitWeapon, Armor *unitArmor);
    Magician(int startX, int startY, Weapon *unitWeapon, Armor *unitArmor,int numberInArray, int health,int armor,int damage,int attackBonus);
    void attack(Unit *unit) override ;
};


#endif //GAME_MAGICIAN_H
