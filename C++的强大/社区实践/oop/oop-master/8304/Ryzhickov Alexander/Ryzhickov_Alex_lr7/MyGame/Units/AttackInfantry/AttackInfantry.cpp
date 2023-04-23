//
// Created by Alex on 21.03.2020.
//

#include "AttackInfantry.h"
namespace GameUnit {
    AttackInfantry::AttackInfantry(int startX, int startY, Weapon *unitWeapon, Armor *unitArmor) : Unit(startX, startY,
                                                                                                        unitWeapon,
                                                                                                        unitArmor) {
    }

    AttackInfantry::AttackInfantry() {}
}