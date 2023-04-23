//
// Created by Alex on 21.03.2020.
//

#ifndef GAME_SWORD_H
#define GAME_SWORD_H


#include "../Weapon.h"

class Sword : public Weapon {
public:
    Sword();
    void upgradeWeapon(unsigned *level, unsigned *money,unsigned *damage) override ;
};


#endif //GAME_SWORD_H
