//
// Created by Alex on 21.03.2020.
//

#ifndef GAME_ROD_H
#define GAME_ROD_H


#include "../Weapon.h"

class Rod: public Weapon {
public:
    Rod();
    void upgradeWeapon(unsigned *level, unsigned *money,unsigned *damage) override ;
};


#endif //GAME_ROD_H
