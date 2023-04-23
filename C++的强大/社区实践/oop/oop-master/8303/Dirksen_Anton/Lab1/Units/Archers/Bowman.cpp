//
// Created by mensch on 02.03.2020.
//

#include "Bowman.h"
#include "../Armor/LeatherArmor.h"
#include "../Weapon/Bow.h"

Bowman::Bowman(){
    health = 70;
    armor = LeatherArmor();
    weapon = Bow();
    range = 5;
}

Texture Bowman::texture() const{
    return BOWMAN;
}