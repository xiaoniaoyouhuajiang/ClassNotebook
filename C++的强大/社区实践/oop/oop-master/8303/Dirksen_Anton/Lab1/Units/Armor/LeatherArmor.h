//
// Created by mensch on 4/4/20.
//

#ifndef OOP_LABS_LEATHERARMOR_H
#define OOP_LABS_LEATHERARMOR_H


#include "Armor.h"

class LeatherArmor : public Armor {
public:
    LeatherArmor(){
        physicDamageReduction = 12;
        magicDamageReduction = 5;
        weight = 7.5;
    }
};


#endif //OOP_LABS_LEATHERARMOR_H
