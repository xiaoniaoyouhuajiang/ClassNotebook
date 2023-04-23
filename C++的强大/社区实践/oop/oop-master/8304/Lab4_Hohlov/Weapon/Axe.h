

#ifndef UNTITLED13_AXE_H
#define UNTITLED13_AXE_H

#include "Weapon.h"

class Axe: public Weapon{

public:

    Axe(){

        damage = 40;
        type = WeaponType::PHYSIC;

    }

};

#endif //UNTITLED13_AXE_H
