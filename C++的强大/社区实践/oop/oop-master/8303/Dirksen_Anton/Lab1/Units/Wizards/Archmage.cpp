//
// Created by mensch on 11.03.2020.
//

#include "Archmage.h"
#include "../Armor/Cloak.h"
#include "../Weapon/SpellBook.h"

Archmage::Archmage(){
    health = 70;
    armor = Cloak();
    weapon = SpellBook();
    mana = 100;
}

Texture Archmage::texture() const{
    return ARCHMAGE;
}