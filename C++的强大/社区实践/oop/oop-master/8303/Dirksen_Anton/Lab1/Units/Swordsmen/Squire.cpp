//
// Created by mensch on 11.03.2020.
//

#include "Squire.h"
#include "../Armor/ChainMail.h"
#include "../Weapon/Dagger.h"

Squire::Squire() {
    health = 100;
    armor = ChainMail();
    weapon = Dagger();
    stamina = 20;
}

Texture Squire::texture() const{
    return SQUIRE;
}