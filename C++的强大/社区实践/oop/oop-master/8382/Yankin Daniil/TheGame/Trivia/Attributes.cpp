#include "Attributes.h"


Health::Health() {
    this->maxHealth = 100;
    this->health = 100;
}

Health::Health(uint16_t maxHealth, uint16_t health) {
    this->maxHealth = maxHealth;
    this->health = health;
}

void Health::setMaxHealth(uint16_t maxHealth) {
    this->maxHealth = maxHealth;
}

void Health::setHealth(uint16_t health) {
    this->health = health;
}

uint16_t Health::getMaxHealth() const {
    return maxHealth;
}

uint16_t Health::getHealth() const {
    return health;
}


Strength::Strength() {
    this->strength = 0;
    this->radius = 0;
}

Strength::Strength(uint16_t strength, uint16_t radius) {
    this->strength = strength;
    this->radius = radius;
}

void Strength::setStrength(uint16_t strength) {
    this->strength = strength;
}

void Strength::setRadius(uint16_t radius) {
    this->radius = radius;
}

uint16_t Strength::getStrength() const {
    return strength;
}

uint16_t Strength::getRadius() const {
    return radius;
}


Armor::Armor() {
    this->armor = 0;
}

Armor::Armor(uint16_t armor) {
    this->armor = armor;
}

void Armor::setArmor(uint16_t armor) {
    this->armor = armor;
}

uint16_t Armor::getArmor() const {
    return armor;
}


MovePoints::MovePoints() {
    this->maxMovePoints = 2;
    this->movePoints = 2;
}

MovePoints::MovePoints(uint16_t maxMovePoints, uint16_t movePoints) {
    this->maxMovePoints = maxMovePoints;
    this->movePoints = movePoints;
}

void MovePoints::setMaxMovePoints(uint16_t maxMovePoints) {
    this->maxMovePoints = maxMovePoints;
}

void MovePoints::setMovePoints(uint16_t movePoints) {
    this->movePoints = movePoints;
}

uint16_t MovePoints::getMaxMovePoints() const {
    return maxMovePoints;
}

uint16_t MovePoints::getMovePoints() const {
    return movePoints;
}
