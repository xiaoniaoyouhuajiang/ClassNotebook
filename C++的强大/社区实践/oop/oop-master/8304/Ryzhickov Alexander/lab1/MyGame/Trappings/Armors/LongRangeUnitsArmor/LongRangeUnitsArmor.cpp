//
// Created by Alex on 08.03.2020.
//

#include "LongRangeUnitsArmor.h"

LongRangeUnitsArmor::LongRangeUnitsArmor() {
    armor = 10;
    level = 1;
    cost = 10;
}

void LongRangeUnitsArmor::upgradeArmor(int *money, int *costUpgrade, int *unitDamage, int *unitWeaponLevel) {
    if (*unitWeaponLevel != 3 && *money > *costUpgrade) {
        switch (*unitWeaponLevel) {
            case 1:
                *unitDamage += 10;
                *costUpgrade += 25;
                break;
            case 2:
                *unitDamage += 10;
                *costUpgrade += 25;
                break;
        }
        *unitWeaponLevel = *unitWeaponLevel + 1;
    }
}
