//
// Created by Alex on 02.03.2020.
//

#ifndef MYGAME_SPEAR_H
#define MYGAME_SPEAR_H


#include "../Weapon.h"

class Spear: public Weapon{
public:
    Spear();
    void upgradeWeapon(int *costUpgrade) override;
};


#endif //MYGAME_SPEAR_H
