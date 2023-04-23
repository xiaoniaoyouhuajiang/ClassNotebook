//
// Created by Alex on 08.03.2020.
//

#include "CavalryArmor.h"

CavalryArmor::CavalryArmor() {
    armor = 25;
    level = 1;
    cost = 50;
}

void CavalryArmor::upgradeArmor(int *money, int *costUpgrade, int *unitDamage, int *unitWeaponLevel) {
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
