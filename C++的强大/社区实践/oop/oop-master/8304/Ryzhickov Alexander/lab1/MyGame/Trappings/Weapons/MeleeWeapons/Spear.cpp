//
// Created by Alex on 02.03.2020.
//

#include "Spear.h"

Spear::Spear() {
    Spear::damage = 30;
    Spear::level = 1;
    Spear::cost = 40;
    Spear::bonus = attackBonus::vsCavalary;
}

void Spear::upgradeWeapon(int *costUpgrade) {
    if (Spear::level != 3 && *costUpgrade > Spear::cost) {
        switch (Spear::level) {
            case 1:
                Spear::damage += 15;
                Spear::cost += 25;
                break;
            case 2:
                Spear::damage += 20;
                Spear::cost += 40;
                break;
        }
        Spear::level++;
    }
}
