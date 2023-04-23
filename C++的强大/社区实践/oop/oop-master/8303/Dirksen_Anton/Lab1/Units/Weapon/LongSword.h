//
// Created by mensch on 4/4/20.
//

#ifndef OOP_LABS_LONGSWORD_H
#define OOP_LABS_LONGSWORD_H


#include "Weapon.h"

class LongSword : public Weapon{
public:
    LongSword(){
        damageType = DamageType::PHYSICAL;
        damage = 30;
    }
};


#endif //OOP_LABS_LONGSWORD_H
