//
// Created by shenk on 16.02.2020.
//

#ifndef UNTITLED13_PISTOL_H
#define UNTITLED13_PISTOL_H

#include "Weapon.h"

class Pistol: public Weapon{

public:

    Pistol(){

        damage = 10;
        type = WeaponType::FIREARMS;

    }

};

#endif //UNTITLED13_PISTOL_H
