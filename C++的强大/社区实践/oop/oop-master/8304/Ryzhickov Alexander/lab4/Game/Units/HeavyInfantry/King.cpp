//
// Created by Alex on 21.03.2020.
//

#include "King.h"

King::King(int startX, int startY, Weapon *unitWeapon, Armor *unitArmor) : HeavyInfantry(startX, startY, unitWeapon, unitArmor) {
    King::health = 1000;
    King::maxHealth = 100;
    King::moves = 2;
}

void King::attack(Unit *unit) {
    unit->setHealth(0);
}
