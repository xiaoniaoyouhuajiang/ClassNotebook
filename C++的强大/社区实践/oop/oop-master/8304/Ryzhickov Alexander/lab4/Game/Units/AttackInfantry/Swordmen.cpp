//
// Created by Alex on 21.03.2020.
//

#include "Swordmen.h"

Swordmen::Swordmen(int startX, int startY, Weapon *unitWeapon, Armor *unitArmor) : AttackInfantry(startX, startY,
                                                                                                  unitWeapon,
                                                                                                  unitArmor) {
    Swordmen::health = 100;
    Swordmen::maxHealth = 100;
}

void Swordmen::attack(Unit *unit) {
    unit->setHealth(0);
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
