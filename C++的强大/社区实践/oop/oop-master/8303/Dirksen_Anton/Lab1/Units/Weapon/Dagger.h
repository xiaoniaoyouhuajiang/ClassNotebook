//
// Created by mensch on 4/4/20.
//

#ifndef OOP_LABS_DAGGER_H
#define OOP_LABS_DAGGER_H


#include "Weapon.h"

class Dagger : public Weapon{
public:
    Dagger(){
        damageType = DamageType::PHYSICAL;
        damage = 18;
    }
};


#endif //OOP_LABS_DAGGER_H
