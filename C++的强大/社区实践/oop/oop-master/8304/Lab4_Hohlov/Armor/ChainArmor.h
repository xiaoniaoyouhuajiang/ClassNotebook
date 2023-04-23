

#ifndef UNTITLED13_CHAINARMOR_H
#define UNTITLED13_CHAINARMOR_H

#include "Armor.h"

class ChainArmor: public Armor{

public:

    ChainArmor(){

        damageAbsorption = 5;
        type = ArmorType::MEDIUM;

    }

};

#endif //UNTITLED13_CHAINARMOR_H
