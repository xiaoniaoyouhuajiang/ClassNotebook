//
// Created by shenk on 16.02.2020.
//

#ifndef UNTITLED13_AVADAKEDAVRA_H
#define UNTITLED13_AVADAKEDAVRA_H

#include <climits>
#include "Weapon.h"

class AvadaKedavra: public Weapon{

public:

    AvadaKedavra(){

        damage = INT_MAX;
        type = WeaponType::MAGIC;

    }

};

#endif //UNTITLED13_AVADAKEDAVRA_H
