//
// Created by Alex on 21.03.2020.
//

#include <iostream>
#include "Unit.h"
#include "RangedUnits/Archer.h"
#include "RangedUnits/Magician.h"
#include "HeavyInfantry/King.h"
#include "HeavyInfantry/Knight.h"
#include "AttackInfantry/Swordmen.h"
#include "AttackInfantry/Spearmen.h"


Unit::Unit(int startX, int startY, Weapon *unitWeapon, Armor *unitArmor) {
    Unit::unitWeapon = unitWeapon;
    Unit::unitArmor = unitArmor;
    Unit::armor = unitArmor->getBaseArmor();
    Unit::damage = unitWeapon->getBaseDamage();
    Unit::x = startX;
    Unit::y = startY;
}

Unit::~Unit() {
    observer->handleEvent(*this);
}

int Unit::getHealth() const {
    return health;
}

int Unit::getArmor() const {
    return armor;
}

int Unit::getDamage() const {
    return damage;
}



unsigned int Unit::getX() const {
    return x;
}

unsigned int Unit::getY() const {
    return y;
}

unsigned int Unit::getNumerInArmy() const {
    return numerInArmy;
}

void Unit::setNumerInArmy(unsigned int numerInArmy) {
    Unit::numerInArmy = numerInArmy;
}

int *Unit::getArmorForGenerator() {
    return &armor;
}

int *Unit::getHealthForGenerator() {
    return &health;
}

void Unit::add(Observer *ref) {
    observer = ref;
    //observers.emplace_back(&ref);
}

Unit::Unit() {

}

void Unit::setAttackBonus(unsigned int attackBonus) {
    Unit::attackBonus = attackBonus;
}

unsigned int Unit::getAttackBonus() const {
    return attackBonus;
}

void Unit::setHealth(unsigned int health) {
    Unit::health = health;
}

void Unit::setMoney(int *money) {
    Unit::money = money;
}

int *Unit::getMoney() const {
    return money;
}

std::string Unit::getInformationAboutUnit() {
    std::string informationAboutUnit;
    informationAboutUnit.append("Unit #" + std::to_string(numerInArmy) + '\n');
    if (dynamic_cast<Archer *>(this) != nullptr) {
        informationAboutUnit.append("Type : Archer\n");
    } else if (dynamic_cast<Magician *>(this) != nullptr) {
        informationAboutUnit.append("Type : Magician\n");
    } else if (dynamic_cast<King *>(this) != nullptr) {
        informationAboutUnit.append("Type : King\n");
    } else if (dynamic_cast<Knight *>(this) != nullptr) {
        informationAboutUnit.append("Type : Knight\n");
    } else if (dynamic_cast<Swordmen *>(this) != nullptr) {
        informationAboutUnit.append("Type : Swordmen\n");
    } else if (dynamic_cast<Spearmen *>(this) != nullptr) {
        informationAboutUnit.append("Type : Spearmen\n");
    }
    informationAboutUnit.append("x : " + std::to_string(x) + '\n');
    informationAboutUnit.append("y : " + std::to_string(y) + '\n');
    informationAboutUnit.append("Health " + std::to_string(health) + '\n');
    informationAboutUnit.append("MaxHealth " + std::to_string(maxHealth) + '\n');
    informationAboutUnit.append("Armor " + std::to_string(armor) + '\n');
    informationAboutUnit.append("MaxArmor " + std::to_string(maxArmor) + '\n');
    informationAboutUnit.append("Damage " + std::to_string(damage) + '\n');
    informationAboutUnit.append("AttackBonus " + std::to_string(attackBonus) + '\n');
    informationAboutUnit.append("\n");
    return informationAboutUnit;
}

void Unit::setX(unsigned int x) {
    Unit::x = x;
}

void Unit::setY(unsigned int y) {
    Unit::y = y;
}
