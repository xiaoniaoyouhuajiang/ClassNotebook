//
// Created by Alex on 21.03.2020.
//

#include "Spearmen.h"
namespace GameUnit {
    Spearmen::Spearmen(int startX, int startY, Weapon *unitWeapon, Armor *unitArmor) : AttackInfantry(startX, startY,
                                                                                                      unitWeapon,
                                                                                                      unitArmor) {
        Spearmen::health = spearmenMaxHealth;
        Spearmen::maxHealth = spearmenMaxHealth;
        Spearmen::maxArmor = spearmenMaxArmor;
    }

    void Spearmen::attack(Unit *unit) {
        unit->setHealth(0);
    }

    Spearmen::Spearmen(int startX, int startY, Weapon *unitWeapon, Armor *unitArmor, int numberInArray, int health,
                       int armor, int damage, int attackBonus) {
        Spearmen::x = startX;
        Spearmen::y = startY;
        Spearmen::unitWeapon = unitWeapon;
        Spearmen::unitArmor = unitArmor;
        Spearmen::numerInArmy = numberInArray;
        Spearmen::health = health;
        Spearmen::maxHealth = spearmenMaxHealth;
        Spearmen::armor = armor;
        Spearmen::maxArmor = spearmenMaxArmor;
        Spearmen::damage = damage;
        Spearmen::attackBonus = attackBonus;
    }
}

