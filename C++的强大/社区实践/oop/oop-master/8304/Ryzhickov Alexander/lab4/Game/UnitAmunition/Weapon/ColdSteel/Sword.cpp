//
// Created by Alex on 21.03.2020.
//

#include "Sword.h"

Sword::Sword() {
    Sword::baseDamage = 20;
    Sword::cost = 20;
    Sword::bonus = 0;
    Sword::maxLevel = 2;
    Sword::damageUpgradeValue = 10;
}

void Sword::upgradeWeapon(unsigned *level, unsigned *money, unsigned *damage) {
    if (*money >= cost && *level != maxLevel) {
        switch (*level) {
            case 0:
                *damage = *damage + Sword::damageUpgradeValue;
                break;
            case 1:
                *damage = *damage + Sword::damageUpgradeValue;
                break;
        }
        Sword::damageUpgradeValue += 10;
        *money = *money - Sword::cost;
        (*level)++;
    }
}
