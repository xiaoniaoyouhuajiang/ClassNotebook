
#ifndef UNTITLED13_STORM_H
#define UNTITLED13_STORM_H

#include <climits>
#include "Weapon.h"

class Storm: public Weapon{

public:

    Storm(){

        damage = 30;
        type = WeaponType::MAGIC;

    }

};

#endif //UNTITLED13_STORM_H
