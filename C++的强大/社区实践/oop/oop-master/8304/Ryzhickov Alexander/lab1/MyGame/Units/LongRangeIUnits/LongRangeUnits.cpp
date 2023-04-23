//
// Created by Alex on 16.02.2020.
//

#include "LongRangeUnits.h"

LongRangeUnits::LongRangeUnits(int startX, int startY, Weapon*unitWeapon, Armor *unitArmor) : Unit(startX, startY, unitWeapon, unitArmor) {
    setMoves(1);
}

void LongRangeUnits::setCountShots(int countShots) {
    LongRangeUnits::countShots = countShots;
}

LongRangeUnits::LongRangeUnits() {

}
