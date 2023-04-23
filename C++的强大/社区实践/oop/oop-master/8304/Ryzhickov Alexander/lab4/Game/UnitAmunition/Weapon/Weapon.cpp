//
// Created by Alex on 21.03.2020.
//

#include "Weapon.h"

unsigned int Weapon::getBaseDamage() const {
    return baseDamage;
}

unsigned int Weapon::getCost() const {
    return cost;
}

unsigned int Weapon::getUpgradeBonus() const {
    return bonus;
}
