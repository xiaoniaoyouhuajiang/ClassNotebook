

#ifndef UNTITLED13_LEATHERARMOR_H
#define UNTITLED13_LEATHERARMOR_H


#include "Armor.h"

class LeatherArmor: public Armor {

public:
    LeatherArmor(){
        damageAbsorption = 3;
        type = ArmorType::LIGHT;
    }

};


#endif //UNTITLED13_LEATHERARMOR_H
