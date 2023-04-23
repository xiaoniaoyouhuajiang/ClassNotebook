//
// Created by shenk on 16.02.2020.
//

#ifndef UNTITLED13_CHAOSIRONARMOR_H
#define UNTITLED13_CHAOSIRONARMOR_H

#include <climits>
#include "Armor.h"

class ChaosIronArmor: public Armor{

public:
    ChaosIronArmor(){

        damageAbsorption = INT_MAX;
        type = ArmorType::HEAVY;

    }

};

#endif //UNTITLED13_CHAOSIRONARMOR_H
