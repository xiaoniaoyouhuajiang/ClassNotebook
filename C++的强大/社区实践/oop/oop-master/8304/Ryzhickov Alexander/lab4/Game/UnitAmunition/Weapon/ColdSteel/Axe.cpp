//
// Created by Alex on 21.03.2020.
//

#include "Axe.h"

Axe::Axe() {
    Axe::baseDamage = 20;
    Axe::cost = 20;
    Axe::bonus = 0;
    Axe::maxLevel = 2;
    Axe::damageUpgradeValue = 10;
}

void Axe::upgradeWeapon(unsigned *level, unsigned *money, unsigned *damage) {
    if (*money >= cost && *level != maxLevel) {
        switch (*level) {
            case 0:
                *damage = *damage + Axe::damageUpgradeValue;
                break;
            case 1:
                *damage = *damage + Axe::damageUpgradeValue;
                break;
        }
        Axe::damageUpgradeValue += 10;
        *money = *money - Axe::cost;
        (*level)++;
    }
}
