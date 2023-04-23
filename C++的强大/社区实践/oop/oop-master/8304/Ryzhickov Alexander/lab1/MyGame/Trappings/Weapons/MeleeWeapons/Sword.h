//
// Created by Alex on 02.03.2020.
//

#ifndef MYGAME_SWORD_H
#define MYGAME_SWORD_H

#include "../Weapon.h"

class Sword : public Weapon{
public:
    Sword();
    void upgradeWeapon(int *costUpgrade) override;
};


#endif //MYGAME_SWORD_H
