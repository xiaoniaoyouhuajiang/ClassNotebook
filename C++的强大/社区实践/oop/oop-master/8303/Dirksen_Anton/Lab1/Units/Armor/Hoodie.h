//
// Created by mensch on 4/4/20.
//

#ifndef OOP_LABS_HOODIE_H
#define OOP_LABS_HOODIE_H


#include "Armor.h"

class Hoodie : public Armor{
public:
    Hoodie(){
        physicDamageReduction = 4;
        magicDamageReduction = 15;
        weight = 0.7;
    }
};


#endif //OOP_LABS_HOODIE_H
