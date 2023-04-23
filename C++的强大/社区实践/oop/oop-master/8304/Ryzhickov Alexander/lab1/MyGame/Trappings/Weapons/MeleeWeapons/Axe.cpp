//
// Created by Alex on 02.03.2020.
//

#include "Axe.h"

Axe::Axe() {
    Axe::damage = 30;
    Axe::level = 1;
    Axe::cost = 25;
    Axe::bonus = attackBonus::vsInfantry;
}

void Axe::upgradeWeapon(int *costUpgrade) {
    if (Axe::level != 3 && *costUpgrade > Axe::cost) {
        switch (Axe::level) {
            case 1:
                Axe::damage += 10;
                Axe::cost += 5;
                break;
            case 2:
                Axe::damage += 15;
                Axe::cost += 10;
                break;
        }
        Axe::level++;
    }
}
