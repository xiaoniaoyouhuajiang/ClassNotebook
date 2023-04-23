//
// Created by mensch on 4/4/20.
//

#ifndef OOP_LABS_CUIRASS_H
#define OOP_LABS_CUIRASS_H


#include "Armor.h"

class Cuirass : public Armor {
public:
    Cuirass(){
        physicDamageReduction = 25;
        magicDamageReduction = 8;
        weight = 18.5;
    }
};


#endif //OOP_LABS_CUIRASS_H
