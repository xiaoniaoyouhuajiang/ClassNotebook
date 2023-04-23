//
// Created by Alex on 21.03.2020.
//

#include "Magician.h"

Magician::Magician(int startX, int startY, Weapon *unitWeapon, Armor *unitArmor) : RangedUnit(startX, startY, unitWeapon, unitArmor) {
    Magician::health = magicianMaxHealth;
    Magician::maxHealth = magicianMaxHealth;
    Magician::countShots = 3;
    Magician::maxArmor = magicianMaxArmor;
}

void Magician::attack(Unit *unit) {
    unit->setHealth(0);
}

Magician::Magician(int startX, int startY, Weapon *unitWeapon, Armor *unitArmor, int numberInArray, int health,int armor, int damage, int attackBonus) {
    Magician::x = startX;
    Magician::y = startY;
    Magician::unitWeapon = unitWeapon;
    Magician::unitArmor = unitArmor;
    Magician::numerInArmy = numberInArray;
    Magician::health = health;
    Magician::maxHealth = magicianMaxHealth;
    Magician::armor = armor;
    Magician::maxArmor = magicianMaxArmor;
    Magician::damage = damage;
    Magician::attackBonus = attackBonus;
}
