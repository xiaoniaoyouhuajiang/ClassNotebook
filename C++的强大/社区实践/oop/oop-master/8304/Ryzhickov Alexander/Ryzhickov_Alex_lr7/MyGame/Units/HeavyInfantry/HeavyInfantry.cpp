//
// Created by Alex on 21.03.2020.
//

#include "HeavyInfantry.h"
namespace GameUnit {
    HeavyInfantry::HeavyInfantry(int startX, int startY, Weapon *unitWeapon, Armor *unitArmor) : Unit(startX, startY,
                                                                                                      unitWeapon,
                                                                                                      unitArmor) {

    }

    HeavyInfantry::HeavyInfantry() {

    }
}