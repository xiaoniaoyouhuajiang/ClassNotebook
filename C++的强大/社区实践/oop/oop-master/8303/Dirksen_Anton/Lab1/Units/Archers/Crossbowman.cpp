//
// Created by mensch on 02.03.2020.
//

#include "Crossbowman.h"
#include "../Armor/ChainMail.h"
#include "../Weapon/Crossbow.h"


Crossbowman::Crossbowman(){
    health = 60;
    armor = ChainMail();
    weapon = Crossbow();
    range = 8;
}

Texture Crossbowman::texture() const{
    return CROSSBOWMAN;
}