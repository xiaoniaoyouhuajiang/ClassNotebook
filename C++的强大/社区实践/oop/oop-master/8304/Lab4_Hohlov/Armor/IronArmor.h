

#ifndef UNTITLED13_IRONARMOR_H
#define UNTITLED13_IRONARMOR_H

#include <climits>
#include "Armor.h"

class IronArmor: public Armor{

public:
    IronArmor(){

        damageAbsorption = INT_MAX;
        type = ArmorType::HEAVY;

    }

};

#endif //UNTITLED13_IRONARMOR_H
