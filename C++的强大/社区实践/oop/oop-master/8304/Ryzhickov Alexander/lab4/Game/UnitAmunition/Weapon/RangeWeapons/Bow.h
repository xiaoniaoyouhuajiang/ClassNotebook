//
// Created by Alex on 21.03.2020.
//

#ifndef GAME_BOW_H
#define GAME_BOW_H


#include "../Weapon.h"

class Bow : public Weapon{
public:
    Bow();
    void upgradeWeapon(unsigned *level, unsigned *money,unsigned *damage) override ;
};


#endif //GAME_BOW_H
