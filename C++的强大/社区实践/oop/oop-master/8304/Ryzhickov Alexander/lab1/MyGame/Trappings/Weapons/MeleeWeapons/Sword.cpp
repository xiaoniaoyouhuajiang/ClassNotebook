//
// Created by Alex on 02.03.2020.
//

#include "Sword.h"

Sword::Sword() {
    Sword::damage = 50;
    Sword::level = 1;
    Sword::cost = 50;
    Sword::bonus = attackBonus::vsInfantry;
}

void Sword::upgradeWeapon(int *costUpgrade) {
    if (Sword::level != 4 && *costUpgrade > Sword::cost) {
        switch (Sword::level) {
            case 1:
                Sword::damage += 10;
                Sword::cost += 10;
                break;
            case 2:
                Sword::damage += 15;
                Sword::cost += 25;
                break;
            case 3:
                Sword::damage += 20;
                Sword::cost += 50;
                break;
        }
        Sword::level++;
    }
}
