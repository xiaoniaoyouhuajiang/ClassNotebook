//
// Created by mensch on 4/4/20.
//

#ifndef OOP_LABS_CROSSBOW_H
#define OOP_LABS_CROSSBOW_H


#include "Weapon.h"

class Crossbow : public Weapon{
public:
    Crossbow(){
        damageType = DamageType::PHYSICAL;
        damage = 38;
    }
};


#endif //OOP_LABS_CROSSBOW_H
