#include "Unit.hpp"

Unit::Unit(Unit &unit) {
    unitName = unit.unitName;
    for (auto & observer : unit.observers)
        observers.push_back(observer);
    coordinates = unit.coordinates;
    attack = unit.attack;
    health = unit.health;
    defense = unit.defense;
}

Unit & Unit::operator=(Unit &unit) {
    if (&unit == this)
        return *this;
    unitName = unit.unitName;
    for (auto & observer : unit.observers)
        observers.push_back(observer);
    coordinates = unit.coordinates;
    attack = unit.attack;
    health = unit.health;
    defense = unit.defense;
    return *this;
}

Unit::Unit(Unit &&unit) {
    std::swap(this->observers, unit.observers);
    std::swap(this->unitName, unit.unitName);
    std::swap(this->coordinates, unit.coordinates);
    std::swap(this->attack, unit.attack);
    std::swap(this->defense, unit.defense);
    std::swap(this->health, unit.health);
}

Unit & Unit::operator=(Unit &&unit) {
    if (&unit == this)
        return *this;
    std::swap(this->observers, unit.observers);
    std::swap(this->unitName, unit.unitName);
    std::swap(this->coordinates, unit.coordinates);
    std::swap(this->attack, unit.attack);
    std::swap(this->defense, unit.defense);
    std::swap(this->health, unit.health);
    return *this;
}

void Unit::setCoordinates(int x, int y) {
    coordinates = new Coordinates;
    coordinates->x = x;
    coordinates->y = y;
}

void Unit::changeAttributes(int attack, int defense, int health) {
    this->attack->changeValue(attack);
    this->health->changeValue(health);
    this->defense->changeValue(defense);
    std::string update = "Update units attributes.";
    notifyObservers(&update);
}

void Unit::setAttributes(int attack, int defense, int health) {
    this->attack = new Attack(attack);
    this->defense = new Defense(defense);
    this->health = new Health(health);
}

void Unit::printAttributeValues() {
    std::cout << "Health: " << health->getValue() << std::endl;
    std::cout << "Defense: " << defense->getValue() << std::endl;
    std::cout << "Attack: " << attack->getValue() << std::endl;
}

void Unit::addObservers(Observer *observer) {
    observers.push_back(observer);
}

void Unit::notifyObservers(std::string *newAction) {
    for (auto & observer : observers){
        observer->update(*newAction);
    }
}
