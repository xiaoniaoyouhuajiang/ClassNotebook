//
// Created by mensch on 11.03.2020.
//

#include "Knight.h"
#include "../Armor/Cuirass.h"
#include "../Weapon/LongSword.h"

Knight::Knight() {
    health = 150;
    armor = Cuirass();
    weapon = LongSword();
    stamina = 10;
}

Texture Knight::texture() const{
    return KNIGHT;
}

