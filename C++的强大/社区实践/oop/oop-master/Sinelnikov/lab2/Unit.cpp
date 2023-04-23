//
// Created by max on 19.02.20.
//

#include <iostream>
#include "Unit.h"
#include "Infantry.h"

void Unit::printXp() {
    if(this != nullptr)
        cout << this->name_of_unit << " xp " <<this->xp << "\n";
    else
        cout << "Юнита на этом поле не существует!!\n";
}

void Unit::printArmour() {
    if(this != nullptr)
        cout << this->name_of_unit << " armour " << this->armour  << "\n";
    else
        cout << "Юнита на этом поле не существует!!\n";
}

void Unit::printAttack() {
    if(this != nullptr)
        cout << this->name_of_unit << " attack " << this->attack << "\n";
    else
        cout << "Юнита на этом поле не существует!!\n";
}

int Unit::getXp() {
    return this->xp;
}

int Unit::getArmour() {
    return this->armour;
}

int Unit::getAttack() {
    return this->attack;
}

void Unit::setParameters(int xp, int armour, int attack,string name_of_init) {
    this->xp = xp;
    this->armour = armour;
    this->attack = attack;
    this->name_of_unit = name_of_init;
}

void Unit::cleanUnitMemory() {
    delete this;
}

void Unit::setId(int id) {
    this->unit_id = id;
}

int Unit::getId() {
    return this->unit_id;
}

int Unit::getMoral() {
    return this->moral;
}

int Unit::getMaxXp() {
    return this->max_xp;
}

int Unit::getMaxMoral() {
    return this->max_moral;
}

void Unit::decreaseMoral(int amount) {
    this->moral-=amount;
}

void Unit::decreaseXp(int amount) {
    this->xp-=amount;
}

void Unit::increaseXp(int amount) {
    if(this->xp + amount <= this->getMaxXp())
        this->xp += amount;
    else
        this->xp = this->getMaxXp();
    cout << "Здоровье увеличено\n";
}

void Unit::increaseMoral(int amount) {
    if(this->moral + amount <= this->getMaxMoral())
        this->moral += amount;
    else
        this->moral = this->getMaxMoral();
    cout << "Мораль увеличена\n";
}

int Unit::getMaxArmour() {
    return this->max_armour;
}

int Unit::getNumberInArray() {
    return this->number_in_array;
}

void Unit::setNumberInArray(int index) {
    this->number_in_array = index;
}

void Unit::setMaxArmour(int armour) {
    this->max_armour = armour;
}

void Unit::repairArmour() {
    this->armour = this->getMaxArmour();
    cout << "Оружие и броня воостановлены\n";
}