//
// Created by Alex on 21.03.2020.
//

#include "Unit.h"


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

unsigned int Unit::getHealth() const {
    return health;
}

unsigned int Unit::getArmor() const {
    return armor;
}

unsigned int Unit::getDamage() const {
    return damage;
}

unsigned int Unit::getMoves() const {
    return moves;
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

unsigned *Unit::getArmorForGenerator() {
    return &armor;
}

unsigned *Unit::getHealthForGenerator() {
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

void Unit::setMoney(unsigned int *money) {
    Unit::money = money;
}

unsigned int *Unit::getMoney() const {
    return money;
}
