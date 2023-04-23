//
// Created by mensch on 4/4/20.
//

#ifndef OOP_LABS_MAGICSTAFF_H
#define OOP_LABS_MAGICSTAFF_H


#include "Weapon.h"

class MagicStaff : public Weapon {
public:
    MagicStaff() {
        damageType = DamageType::MAGICAL;
        damage = 20;
    }
};


#endif //OOP_LABS_MAGICSTAFF_H
