
#ifndef UNTITLED13_SWORD_H
#define UNTITLED13_SWORD_H

#include "Weapon.h"

class Sword: public Weapon{

public:
    Sword(){

        damage = 10;
        type = WeaponType::PHYSIC;

    }

};

#endif //UNTITLED13_SWORD_H
