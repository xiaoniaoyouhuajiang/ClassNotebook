//
// Created by Alex on 21.03.2020.
//

#include "Weapon.h"
namespace GameUnit {
    unsigned int Weapon::getBaseDamage() const {
        return baseDamage;
    }

    unsigned int Weapon::getCost() const {
        return cost;
    }

    unsigned int Weapon::getUpgradeBonus() const {
        return bonus;
    }
}