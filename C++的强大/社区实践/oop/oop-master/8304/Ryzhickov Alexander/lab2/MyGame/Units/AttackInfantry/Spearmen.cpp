//
// Created by Alex on 21.03.2020.
//

#include "Spearmen.h"

Spearmen::Spearmen(int startX, int startY, Weapon *unitWeapon, Armor *unitArmor) : AttackInfantry(startX, startY, unitWeapon, unitArmor) {
    Spearmen::health = 100;
    Spearmen::maxHealth = 100;
}

void Spearmen::attack(Unit *unit) {
    unit->setHealth(0);
}
