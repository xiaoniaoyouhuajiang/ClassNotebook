//
// Created by therealyou on 11.02.2020.
//

#include "Unit.h"

int Unit::getX() const {
    return x;
}

void Unit::setX(int x) {
    this->x = x;
}

int Unit::getY() const {
    return y;
}

void Unit::setY(int y) {
    this->y = y;
}

void Unit::setGameField(GameField *gameField) {
    this->gameField = gameField;
}

double Unit::minAttribute(double attribute) {
    return attribute - deltaAttribute(attribute);
}

double Unit::deltaAttribute(double attribute) {
    return attribute * SCATTER;
}

double Unit::getSpeed() const {
    return speed;
}

double Unit::getHealth() const {
    return health;
}

double Unit::getArmor() const {
    return armor;
}

double Unit::getDamage() const {
    return damage;
}

GameField *Unit::getGameField() const {
    return gameField;
}

void Unit::move(int dx, int dy) {
    this->canAdded = true;
    if (this->getGameField()->addUnit(this, x + dx, y + dy)){
        std::cerr << "\t\tCan not move unit to another place" << std::endl;
        this->canAdded = false;
        return;
    }
    this->getGameField()->deleteUnit(x - dx, y - dy);
//    x += dx;
//    y += dy;
}

void Unit::addUnit() {
    this->canAdded = false;
}

void Unit::deleteUnit() {
    this->canAdded = true;
}

bool Unit::isCanAdded() const {
    return canAdded;
}

void Unit::print() {
    char id = this->getId();
    char *name = (char*) malloc(10 * sizeof(char));
    switch (id){
        case 'P':
            strcpy(name, "Peon");
            break;
        case 'S':
            strcpy(name, "Shooter");
            break;
        case 'E':
            strcpy(name, "Elf");
            break;
        case 'W':
            strcpy(name, "Witch");
            break;
        case 'T':
            strcpy(name, "Troll");
            break;
        case 'G':
            strcpy(name, "Goblin");
            break;
    }
    std::cout << "[" << name << "]" << std::endl <<
    "Armor: " << this->getArmor() << std::endl <<
    "Speed: " << this->getSpeed() << std::endl <<
    "Damage: " << this->getDamage() << std::endl <<
    "Health: " << this->getHealth() << std::endl <<

    "Current position: " << std::endl <<
    "X: " << this->getX() << std::endl <<
    "Y: " << this->getY() << std::endl <<

    std::endl << std::endl;
}


void Unit::setDamage(int damage) {
    std::srand(unsigned(std::time(0)));
    double min = minAttribute(damage);
    this->damage = min + static_cast<double >(std::rand())/RAND_MAX * 2 * deltaAttribute(min);
}

void Unit::setArmor(int armor) {
    std::srand(unsigned(std::time(0)));
    double min = minAttribute(armor);
    this->armor = min + static_cast<double >(std::rand())/RAND_MAX * 2 * deltaAttribute(min);
}

void Unit::setHealth(int health) {
    std::srand(unsigned(std::time(0)));
    double min = minAttribute(health);
    this->health = min + static_cast<double >(std::rand())/RAND_MAX * 2 * deltaAttribute(min);
}

void Unit::setSpeed(int speed) {
    std::srand(unsigned(std::time(0)));
    double min = minAttribute(speed);
    this->speed = min + static_cast<double >(std::rand())/RAND_MAX * 2 * deltaAttribute(min);
}

Unit::Unit(int speed, int armor, int damage, int health) {
    setArmor(armor);
    setDamage(damage);
    setHealth(health);
    setSpeed(speed);
}
