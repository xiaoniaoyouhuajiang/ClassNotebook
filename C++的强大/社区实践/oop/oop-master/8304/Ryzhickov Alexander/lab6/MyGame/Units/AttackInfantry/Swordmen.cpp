//
// Created by Alex on 21.03.2020.
//

#include "Swordmen.h"

Swordmen::Swordmen(int startX, int startY, Weapon *unitWeapon, Armor *unitArmor) : AttackInfantry(startX, startY,
                                                                                                  unitWeapon,
                                                                                                  unitArmor) {
    Swordmen::health = swordmenMaxHealth;
    Swordmen::maxHealth = swordmenMaxHealth;
    Swordmen::maxArmor = swordmenMaxArmor;
}

void Swordmen::attack(Unit *unit) {
    unit->setHealth(0);
}

Swordmen::Swordmen(int startX, int startY, Weapon *unitWeapon, Armor *unitArmor, int numberInArray, int health,
                   int armor, int damage, int attackBonus){
    Swordmen::x = startX;
    Swordmen::y = startY;
    Swordmen::unitWeapon = unitWeapon;
    Swordmen::unitArmor = unitArmor;
    Swordmen::numerInArmy = numberInArray;
    Swordmen::health = health;
    Swordmen::maxHealth = swordmenMaxHealth;
    Swordmen::armor = armor;
    Swordmen::maxArmor = swordmenMaxArmor;
    Swordmen::damage = damage;
    Swordmen::attackBonus = attackBonus;
}


/*Swordmen::Swordmen(const Swordmen &swordmen){
    delete unitWeapon;
    delete unitArmor;
    unitArmor = swordmen.unitArmor;
    unitWeapon = swordmen.unitWeapon;
    health = swordmen.getHealth();
    armor = swordmen.getArmor();
    damage = swordmen.getDamage();
    moves = swordmen.getMoves();
    numerInArmy = swordmen.getNumerInArmy();
}



Swordmen::Swordmen(Swordmen &&swordmen) {
    delete unitWeapon;
    delete unitArmor;
    unitArmor = swordmen.unitArmor;
    unitWeapon = swordmen.unitWeapon;
    health = swordmen.getHealth();
    armor = swordmen.getArmor();
    damage = swordmen.getDamage();
    moves = swordmen.getMoves();
    numerInArmy = swordmen.getNumerInArmy();
    swordmen.unitWeapon = nullptr;
    swordmen.unitArmor = nullptr;
}*/
