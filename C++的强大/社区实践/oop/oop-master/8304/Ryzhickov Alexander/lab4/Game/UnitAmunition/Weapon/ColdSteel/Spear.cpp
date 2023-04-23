//
// Created by Alex on 21.03.2020.
//

#include "Spear.h"

Spear::Spear() {
    Spear::baseDamage = 20;
    Spear::cost = 20;
    Spear::bonus = 0;
    Spear::maxLevel = 2;
    Spear::damageUpgradeValue = 10;
}

void Spear::upgradeWeapon(unsigned *level, unsigned *money, unsigned *damage) {
    if (*money >= cost && *level != maxLevel) {
        switch (*level) {
            case 0:
                *damage = *damage + Spear::damageUpgradeValue;
                break;
            case 1:
                *damage = *damage + Spear::damageUpgradeValue;
                break;
        }
        Spear::damageUpgradeValue += 10;
        *money = *money - Spear::cost;
        (*level)++;
    }
}


