//
// Created by Alex on 21.03.2020.
//

#include "AttackUnitArmor.h"

AttackUnitArmor::AttackUnitArmor() {
    AttackUnitArmor::baseArmor = 50;
    AttackUnitArmor::cost = 50;
    AttackUnitArmor::maxLevel = 2;
    AttackUnitArmor::armorUpgradeValue = 10;
}

void AttackUnitArmor::upgradeArmor(unsigned *level, unsigned *money, unsigned *damage) {
    if (*money >= cost && *level != maxLevel) {
        switch (*level) {
            case 0:
                *damage = *damage + AttackUnitArmor::armorUpgradeValue;
                break;
            case 1:
                *damage = *damage + AttackUnitArmor::armorUpgradeValue;
                break;
        }
        AttackUnitArmor::armorUpgradeValue += 10;
        *money = *money - AttackUnitArmor::cost;
        (*level)++;
    }
}


