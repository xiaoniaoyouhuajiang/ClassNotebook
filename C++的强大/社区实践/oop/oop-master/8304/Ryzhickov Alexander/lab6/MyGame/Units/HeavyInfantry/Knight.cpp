//
// Created by Alex on 21.03.2020.
//

#include "Knight.h"

Knight::Knight(int startX, int startY, Weapon *unitWeapon, Armor *unitArmor) : HeavyInfantry(startX, startY, unitWeapon, unitArmor) {
    Knight::health = knightMaxHealth;
    Knight::maxHealth = knightMaxHealth;
    Knight::maxArmor = knightMaxArmor;
}

void Knight::attack(Unit *unit) {
    unit->setHealth(0);
}

Knight::Knight(int startX, int startY, Weapon *unitWeapon, Armor *unitArmor,int numberInArray, int health,int armor,int damage,int attackBonus) {
    Knight::x = startX;
    Knight::y = startY;
    Knight::unitWeapon = unitWeapon;
    Knight::unitArmor = unitArmor;
    Knight::numerInArmy = numberInArray;
    Knight::health = health;
    Knight::maxHealth = knightMaxHealth;
    Knight::armor = armor;
    Knight::maxArmor = knightMaxArmor;
    Knight::damage = damage;
    Knight::attackBonus = attackBonus;
}
