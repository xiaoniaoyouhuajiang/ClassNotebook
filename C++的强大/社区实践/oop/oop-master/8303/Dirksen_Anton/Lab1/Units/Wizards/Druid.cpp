//
// Created by mensch on 11.03.2020.
//

#include "Druid.h"
#include "../Armor/Hoodie.h"
#include "../Weapon/MagicStaff.h"

Druid::Druid(){
    health = 60;
    armor = Hoodie();
    weapon = MagicStaff();
    mana = 60;
}

Texture Druid::texture() const{
    return DRUID;
}