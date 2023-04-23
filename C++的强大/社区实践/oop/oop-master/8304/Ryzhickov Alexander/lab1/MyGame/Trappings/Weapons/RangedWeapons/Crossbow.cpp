//
// Created by Alex on 02.03.2020.
//

#include "Crossbow.h"

Crossbow::Crossbow() {
    Crossbow::damage = 15;
    Crossbow::level = 1;
    Crossbow::cost = 50;
    Crossbow::bonus = attackBonus::vsInfantry;
}

void Crossbow::upgradeWeapon(int *costUpgrade) {
    if (Crossbow::level != 3 && *costUpgrade > Crossbow::cost) {
        switch (Crossbow::level) {
            case 1:
                Crossbow::damage += 10;
                Crossbow::cost += 25;
                break;
            case 2:
                Crossbow::damage += 15;
                Crossbow::cost += 25;
                break;
        }
        Crossbow::level++;
    }
}
