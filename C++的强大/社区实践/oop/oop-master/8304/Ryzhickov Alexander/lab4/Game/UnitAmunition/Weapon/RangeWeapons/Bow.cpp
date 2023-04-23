//
// Created by Alex on 21.03.2020.
//

#include "Bow.h"

Bow::Bow() {
    Bow::baseDamage = 20;
    Bow::cost = 20;
    Bow::bonus = 0;
    Bow::maxLevel = 2;
    Bow::damageUpgradeValue = 10;
}

void Bow::upgradeWeapon(unsigned *level, unsigned *money, unsigned *damage) {
    if (*money >= cost && *level != maxLevel) {
        switch (*level) {
            case 0:
                *damage = *damage + Bow::damageUpgradeValue;
                break;
            case 1:
                *damage = *damage + Bow::damageUpgradeValue;
                break;
        }
        Bow::damageUpgradeValue += 10;
        *money = *money - Bow::cost;
        (*level)++;
    }
}
