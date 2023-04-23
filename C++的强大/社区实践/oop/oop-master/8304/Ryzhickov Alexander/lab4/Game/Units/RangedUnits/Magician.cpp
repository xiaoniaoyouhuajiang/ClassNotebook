//
// Created by Alex on 21.03.2020.
//

#include "Magician.h"

Magician::Magician(int startX, int startY, Weapon *unitWeapon, Armor *unitArmor) : RangedUnit(startX, startY, unitWeapon, unitArmor) {
    Magician::health = 100;
    Magician::maxHealth = 100;
    Magician::countShots = 3;
}

void Magician::attack(Unit *unit) {
    unit->setHealth(0);
}
