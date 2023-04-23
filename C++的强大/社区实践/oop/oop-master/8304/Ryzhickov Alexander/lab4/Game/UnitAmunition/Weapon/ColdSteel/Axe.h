//
// Created by Alex on 21.03.2020.
//

#ifndef GAME_AXE_H
#define GAME_AXE_H


#include "../Weapon.h"

class Axe : public Weapon{
public:
    Axe();
    void upgradeWeapon(unsigned *level, unsigned *money,unsigned *damage) override ;
};


#endif //GAME_AXE_H
