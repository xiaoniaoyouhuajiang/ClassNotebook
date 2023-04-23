//
// Created by mensch on 4/4/20.
//

#ifndef OOP_LABS_SPELLBOOK_H
#define OOP_LABS_SPELLBOOK_H


#include "Weapon.h"

class SpellBook : public Weapon{
public:
    SpellBook() {
        damageType = DamageType::MAGICAL;
        damage = 45;
    }
};


#endif //OOP_LABS_SPELLBOOK_H
