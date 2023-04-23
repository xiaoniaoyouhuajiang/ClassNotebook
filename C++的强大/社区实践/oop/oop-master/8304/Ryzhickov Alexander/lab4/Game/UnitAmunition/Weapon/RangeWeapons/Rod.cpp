//
// Created by Alex on 21.03.2020.
//

#include "Rod.h"

Rod::Rod() {
    Rod::baseDamage = 20;
    Rod::cost = 20;
    Rod::bonus = 0;
    Rod::maxLevel = 2;
    Rod::damageUpgradeValue = 10;
}

void Rod::upgradeWeapon(unsigned *level, unsigned *money, unsigned *damage) {
    if (*money >= cost && *level != maxLevel) {
        switch (*level) {
            case 0:
                *damage = *damage + Rod::damageUpgradeValue;
                break;
            case 1:
                *damage = *damage + Rod::damageUpgradeValue;
                break;
        }
        Rod::damageUpgradeValue += 10;
        *money = *money - Rod::cost;
        (*level)++;
    }
}
