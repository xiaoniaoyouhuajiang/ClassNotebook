//
// Created by Alex on 21.03.2020.
//

#include "HeavyUnitArmor.h"

HeavyUnitArmor::HeavyUnitArmor() {
    HeavyUnitArmor::baseArmor = 50;
    HeavyUnitArmor::cost = 50;
    HeavyUnitArmor::maxLevel = 2;
    HeavyUnitArmor::armorUpgradeValue = 10;
}

void HeavyUnitArmor::upgradeArmor(unsigned *level, unsigned *money, unsigned *damage) {
    if (*money >= cost && *level != maxLevel) {
        switch (*level) {
            case 0:
                *damage = *damage + HeavyUnitArmor::armorUpgradeValue;
                break;
            case 1:
                *damage = *damage + HeavyUnitArmor::armorUpgradeValue;
                break;
        }
        HeavyUnitArmor::armorUpgradeValue += 10;
        *money = *money - HeavyUnitArmor::cost;
        (*level)++;
    }
}

