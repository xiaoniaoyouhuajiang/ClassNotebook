//
// Created by mensch on 4/4/20.
//

#ifndef OOP_LABS_BOW_H
#define OOP_LABS_BOW_H


#include "Weapon.h"

class Bow : public Weapon {
public:
    Bow(){
        damageType = DamageType::PHYSICAL;
        damage = 10;
    }
};


#endif //OOP_LABS_BOW_H
