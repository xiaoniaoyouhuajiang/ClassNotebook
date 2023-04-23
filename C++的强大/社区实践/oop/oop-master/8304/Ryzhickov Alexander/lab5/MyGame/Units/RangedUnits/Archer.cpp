//
// Created by Alex on 21.03.2020.
//

#include "Archer.h"

Archer::Archer(int startX, int startY, Weapon *unitWeapon, Armor *unitArmor) : RangedUnit(startX, startY, unitWeapon, unitArmor) {
    Archer::health = archerMaxHealth;
    Archer::maxHealth = archerMaxHealth;
    Archer::countShots = 1;
    Archer::maxArmor = archerMaxArmor;

}

void Archer::attack(Unit *unit) {
    unit->setHealth(0);
}

Archer::Archer(int startX, int startY, Weapon *unitWeapon, Armor *unitArmor, int numberInArray, int health, int armor,int damage, int attackBonus) {
    Archer::x = startX;
    Archer::y = startY;
    Archer::unitWeapon = unitWeapon;
    Archer::unitArmor = unitArmor;
    Archer::numerInArmy = numberInArray;
    Archer::health = health;
    Archer::maxHealth = archerMaxHealth;
    Archer::armor = armor;
    Archer::maxArmor = archerMaxArmor;
    Archer::damage = damage;
    Archer::attackBonus = attackBonus;
}
