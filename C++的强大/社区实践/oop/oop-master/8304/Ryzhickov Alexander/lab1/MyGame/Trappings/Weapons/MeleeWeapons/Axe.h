//
// Created by Alex on 02.03.2020.
//

#ifndef MYGAME_AXE_H
#define MYGAME_AXE_H


#include "../Weapon.h"

class Axe: public Weapon {
public:
    Axe();
    void upgradeWeapon(int *costUpgrade) override;
};


#endif //MYGAME_AXE_H
