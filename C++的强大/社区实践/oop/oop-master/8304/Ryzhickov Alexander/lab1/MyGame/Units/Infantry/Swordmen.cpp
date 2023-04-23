//
// Created by Alex on 16.02.2020.
//

#include "Swordmen.h"
#include "../../Trappings/Weapons/MeleeWeapons/Sword.h"
#include "../../HelpersClasses/Data.h"

Swordmen::Swordmen(int startX, int startY, Weapon*unitWeapon, Armor *unitArmor) : Infantry(startX, startY, unitWeapon, unitArmor) {
    setHealth(healthSwordmen);
}

void Swordmen::stronger() {

}

Swordmen::Swordmen(const Swordmen &swordmen){
    unitPosition = new Position(0, 0);
    unitPosition->setNewPositionX(swordmen.unitPosition->getPositionX());
    unitPosition->setNewPositionY(swordmen.unitPosition->getPositionY());
    unitArmor = swordmen.unitArmor;
    unitWeapon = swordmen.unitWeapon;
    health = swordmen.getHealth();
    armor = swordmen.getArmor();
    damage = swordmen.getDamage();
    moves = swordmen.getMoves();
    numerInArmy = swordmen.getNumerInArmy();
}

void Swordmen::attack() {

}

Swordmen::Swordmen(Swordmen &&swordmen) {
    delete unitPosition;
    unitPosition = new Position(0, 0);
    unitPosition->setNewPositionX(swordmen.unitPosition->getPositionX());
    unitPosition->setNewPositionY(swordmen.unitPosition->getPositionY());
    unitArmor = swordmen.unitArmor;
    unitWeapon = swordmen.unitWeapon;
    health = swordmen.getHealth();
    armor = swordmen.getArmor();
    damage = swordmen.getDamage();
    moves = swordmen.getMoves();
    numerInArmy = swordmen.getNumerInArmy();
    swordmen.unitPosition = nullptr;
}

