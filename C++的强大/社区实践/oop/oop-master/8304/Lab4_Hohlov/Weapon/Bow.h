
#ifndef UNTITLED13_BOW_H
#define UNTITLED13_BOW_H

#include "Weapon.h"

class Bow: public Weapon{

public:

    Bow(){

        damage = 10;
        type = WeaponType::FAR;

    }

};

#endif //UNTITLED13_BOW_H
