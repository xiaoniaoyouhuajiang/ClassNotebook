//
// Created by Alex on 16.02.2020.
//

#include "Archer.h"
#include "../../Trappings/Weapons/RangedWeapons/ShortBow.h"
#include "../../Trappings/Weapons/RangedWeapons/LongBow.h"
#include "../../HelpersClasses/Data.h"

Archer::Archer(int startX, int startY, Weapon*unitWeapon, Armor *unitArmor) : LongRangeUnits(startX, startY, unitWeapon, unitArmor) {
    setHealth(healthSwordmen);
    setCountShots(countShotsArchers);
}

Archer::Archer(const Archer &archer) {
    unitPosition = new Position(0, 0);
    unitPosition->setNewPositionX(archer.unitPosition->getPositionX());
    unitPosition->setNewPositionY(archer.unitPosition->getPositionY());
    unitArmor = archer.unitArmor;
    unitWeapon = archer.unitWeapon;
    health = archer.getHealth();
    armor = archer.getArmor();
    damage = archer.getDamage();
    moves = archer.getMoves();
    numerInArmy = archer.getNumerInArmy();
}

Archer::Archer(Archer &&archers){
    unitPosition = new Position(0, 0);
    unitPosition->setNewPositionX(archers.unitPosition->getPositionX());
    unitPosition->setNewPositionY(archers.unitPosition->getPositionY());
    health = archers.getHealth();
    armor = archers.getArmor();
    damage = archers.getDamage();
    moves = archers.getMoves();
    numerInArmy = archers.getNumerInArmy();

    archers.unitPosition = nullptr;
}

void Archer::attack() {

}
