#include "Unit.h"
#include "../HelpersClasses/Base/Base.h"

int Unit::getHealth() const {
    return health;
}

int Unit::getArmor() const {
    return armor;
}

int Unit::getDamage() const {
    return damage;
}

void Unit::setHealth(int health) {
    Unit::health = health;
}

void Unit::setArmor(int armor) {
    Unit::armor = armor;
}

void Unit::setDamage(int damage) {
    Unit::damage = damage;
}

void Unit::setNewPosition(int newX, int newY) {
    Unit::unitPosition->setNewPositionX(newX);
    Unit::unitPosition->setNewPositionY(newY);
}

void Unit::setMoves(int moves) {
    Unit::moves = moves;
}

Unit::~Unit() {
    base->handleEvent(*this);
    delete unitPosition;
}

int Unit::getNumerInArmy() const {
    return numerInArmy;
}

void Unit::setNumerInArmy(int numerInArmy) {
    Unit::numerInArmy = numerInArmy;
}

Unit::Unit() {
    Unit::unitPosition = nullptr;
    Unit::health = 0;
    Unit::armor = 0;
    Unit::damage = 0;
    Unit::moves = 0;
    Unit::numerInArmy = -1;
}

int Unit::getMoves() const {
    return moves;
}

Position *Unit::getPosition() const {
    return unitPosition;
}

Unit::Unit(int startX, int startY, Weapon *unitWeapon, Armor *unitArmor) {
    Unit::unitPosition = new Position(startX, startY);
    Unit::unitWeapon = unitWeapon;
    Unit::unitArmor = unitArmor;
    Unit::armor = unitArmor->getArmor();
    Unit::damage = unitWeapon->getDamage();
}

int* Unit::getArmorForGenerator() {
    return &armor;
}

int *Unit::getHealthForGenerator() {
    return &health;
}


void Unit::add(Base *ref) {
    base = ref;
   //observers.emplace_back(&ref);
}
/*
void Unit::add(Base ref) {

}*/
