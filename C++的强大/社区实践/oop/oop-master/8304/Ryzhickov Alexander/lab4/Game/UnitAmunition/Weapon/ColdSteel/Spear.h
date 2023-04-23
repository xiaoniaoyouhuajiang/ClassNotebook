//
// Created by Alex on 21.03.2020.
//

#ifndef GAME_SPEAR_H
#define GAME_SPEAR_H


#include "../Weapon.h"

class Spear : public Weapon{
public:
    Spear();
    void upgradeWeapon(unsigned *level, unsigned *money,unsigned *damage) override ;
};


#endif //GAME_SPEAR_H
