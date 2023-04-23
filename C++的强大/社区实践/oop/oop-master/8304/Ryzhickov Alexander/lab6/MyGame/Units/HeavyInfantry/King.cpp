//
// Created by Alex on 21.03.2020.
//

#include "King.h"

King::King(int startX, int startY, Weapon *unitWeapon, Armor *unitArmor) : HeavyInfantry(startX, startY, unitWeapon, unitArmor) {
    King::health = kingMaxHealth;
    King::maxHealth = kingMaxHealth;
    King::maxArmor = kingMaxArmor;
}

void King::attack(Unit *unit) {
    unit->setHealth(0);
}

King::King(int startX, int startY, Weapon *unitWeapon, Armor *unitArmor, int numberInArray, int health, int armor,int damage, int attackBonus) {
    King::x = startX;
    King::y = startY;
    King::unitWeapon = unitWeapon;
    King::unitArmor = unitArmor;
    King::numerInArmy = numberInArray;
    King::health = health;
    King::maxHealth = kingMaxHealth;
    King::armor = armor;
    King::maxArmor = kingMaxArmor;
    King::damage = damage;
    King::attackBonus = attackBonus;
}

