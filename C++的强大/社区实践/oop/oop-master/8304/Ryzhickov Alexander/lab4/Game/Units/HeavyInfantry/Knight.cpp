//
// Created by Alex on 21.03.2020.
//

#include "Knight.h"

Knight::Knight(int startX, int startY, Weapon *unitWeapon, Armor *unitArmor) : HeavyInfantry(startX, startY, unitWeapon, unitArmor) {
    Knight::health = 100;
    Knight::maxHealth = 100;
    Knight::moves = 2;
}

void Knight::attack(Unit *unit) {
    unit->setHealth(0);
}
