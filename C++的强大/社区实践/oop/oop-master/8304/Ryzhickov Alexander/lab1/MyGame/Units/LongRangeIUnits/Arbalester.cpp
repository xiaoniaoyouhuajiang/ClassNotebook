//
// Created by Alex on 16.02.2020.
//

#include "Arbalester.h"
#include "../../Trappings/Weapons/RangedWeapons/Crossbow.h"
#include "../../HelpersClasses/Data.h"

Arbalester::Arbalester(int startX, int startY, Weapon*unitWeapon, Armor *unitArmor) : LongRangeUnits(startX, startY, unitWeapon, unitArmor) {
    setHealth(healthSwordmen);
    setCountShots(countShotsArbalesters);
}

Arbalester::Arbalester(const Arbalester &arbalester) {
    unitPosition = new Position(0, 0);
    unitPosition->setNewPositionX(arbalester.unitPosition->getPositionX());
    unitPosition->setNewPositionY(arbalester.unitPosition->getPositionY());
    unitArmor =arbalester.unitArmor;
    unitWeapon =arbalester.unitWeapon;
    health = arbalester.getHealth();
    armor = arbalester.getArmor();
    damage = arbalester.getDamage();
    moves = arbalester.getMoves();
    numerInArmy = arbalester.getNumerInArmy();
}

Arbalester::Arbalester(Arbalester &&arbalester){
    unitPosition = new Position(0, 0);
    unitPosition->setNewPositionX(arbalester.unitPosition->getPositionX());
    unitPosition->setNewPositionY(arbalester.unitPosition->getPositionY());
    unitArmor =arbalester.unitArmor;
    unitWeapon =arbalester.unitWeapon;
    health = arbalester.getHealth();
    armor = arbalester.getArmor();
    damage = arbalester.getDamage();
    moves = arbalester.getMoves();
    numerInArmy = arbalester.getNumerInArmy();

    arbalester.unitPosition = nullptr;
}

void Arbalester::attack() {

}
