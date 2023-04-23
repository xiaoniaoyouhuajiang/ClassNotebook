//
// Created by Mila on 23.02.2020.
//

#include "Unit.h"

int Unit::getHealth() const {
    return health;
}

void Unit::setHealth(int health) {
    Unit::health = health;
}

int Unit::getArmor() const {
    return armor;
}

void Unit::setArmor(unsigned armor) {
    Unit::armor = armor;
}

int Unit::getDamage() const {
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

void Unit::subscribeObserver(Observer *observer) {
    Unit::observer = observer;
}

unsigned int Unit::getNumberInArray() const {
    return numberInArray;
}

void Unit::setNumberInArray(unsigned int numberArray) {
    Unit::numberInArray = numberArray;
}

int *Unit::getHealthForUpdate() {
    return &health;
}

int* Unit:: getArmorForUpdate(){
    return &armor;
}

int* Unit::getDamageForUpdate() {
    return &damage;
}

void Unit::attack(Unit *unit) {
    unit->setHealth(unit->getHealth()-damage);

}