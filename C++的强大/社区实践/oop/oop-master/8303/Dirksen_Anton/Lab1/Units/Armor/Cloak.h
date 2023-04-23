//
// Created by mensch on 4/4/20.
//

#ifndef OOP_LABS_CLOAK_H
#define OOP_LABS_CLOAK_H


#include "Armor.h"

class Cloak : public Armor {
public:
    Cloak(){
        physicDamageReduction = 8;
        magicDamageReduction = 25;
        weight = 3.7;
    }
};


#endif //OOP_LABS_CLOAK_H
