//
// Created by shenk on 16.02.2020.
//

#ifndef UNTITLED13_SWORDMAN_H
#define UNTITLED13_SWORDMAN_H

#include "Infantry.h"
#include "../../../Weapon/Sword.h"

class SwordMan: public Infantry{

public:

    SwordMan(): Infantry(*WeaponFlyWeight::getFlyWeight<Sword>(), 100){}

};

#endif //UNTITLED13_SWORDMAN_H
