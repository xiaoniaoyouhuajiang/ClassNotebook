
#ifndef UNTITLED13_FIREBALL_H
#define UNTITLED13_FIREBALL_H

#include "Weapon.h"

class Fireball: public Weapon{

public:

    Fireball(){

        damage = 10;
        type = WeaponType::MAGIC;

    }

};

#endif //UNTITLED13_FIREBALL_H
