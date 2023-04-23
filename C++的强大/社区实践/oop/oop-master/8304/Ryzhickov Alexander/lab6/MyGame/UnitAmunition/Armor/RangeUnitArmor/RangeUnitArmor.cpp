//
// Created by Alex on 21.03.2020.
//

#include "RangeUnitArmor.h"

RangeUnitArmor::RangeUnitArmor() {
    RangeUnitArmor::baseArmor = 50;
    RangeUnitArmor::cost = 50;
    RangeUnitArmor::maxLevel = 2;
    RangeUnitArmor::armorUpgradeValue = 10;
}

void RangeUnitArmor::upgradeArmor(unsigned *level, unsigned *money, unsigned *damage) {
    if (*money >= cost && *level != maxLevel) {
        switch (*level) {
            case 0:
                *damage = *damage + RangeUnitArmor::armorUpgradeValue;
                break;
            case 1:
                *damage = *damage + RangeUnitArmor::armorUpgradeValue;
                break;
        }
        RangeUnitArmor::armorUpgradeValue += 10;
        *money = *money - RangeUnitArmor::cost;
        (*level)++;
    }
}
