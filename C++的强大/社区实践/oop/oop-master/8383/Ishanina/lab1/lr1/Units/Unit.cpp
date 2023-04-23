//
// Created by Mila on 23.02.2020.
//

#include "Unit.h"

unsigned Unit::getHealth() const {
    return health;
}

void Unit::setHealth(unsigned health) {
    Unit::health = health;
}

unsigned Unit::getArmor() const {
    return armor;
}

void Unit::setArmor(unsigned armor) {
    Unit::armor = armor;
}

unsigned Unit::getDamage() const {
    return damage;
}

void Unit::setDamage(unsigned damage) {
    this->damage = damage;
}

char Unit::getName() const {
    return name;
}

void Unit::setName(char name) {
    Unit::name = name;
}








