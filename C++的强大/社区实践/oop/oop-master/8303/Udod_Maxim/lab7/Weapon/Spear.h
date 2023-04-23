//
// Created by shenk on 16.02.2020.
//

#ifndef UNTITLED13_SPEAR_H
#define UNTITLED13_SPEAR_H

#include "Weapon.h"

class Spear: public Weapon{

public:

    Spear(){

        damage = 20;
        type = WeaponType::PHYSIC;

    }

};

#endif //UNTITLED13_SPEAR_H
