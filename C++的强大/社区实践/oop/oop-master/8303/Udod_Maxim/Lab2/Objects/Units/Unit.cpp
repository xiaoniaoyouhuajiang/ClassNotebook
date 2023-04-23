//
// Created by shenk on 14.02.2020.
//

#include "Unit.h"
#include "../Neutrals/NeutralObjectStrategy/InfantryStrategy.h"
#include "../Neutrals/NeutralObjectStrategy/ArcherStrategy.h"
#include "../Neutrals/NeutralObjectStrategy/WizardStrategy.h"

Unit::Unit(const Unit &other):
GameObject(ObjectType::UNIT),
armor(other.armor),
weapon(other.weapon),
health(other.health) {}

void Unit::addObserver(UnitObserver *observer) {

    observers.push_back(observer);

}

void Unit::move(Point point) {

    for (auto o: observers){
        o->onUnitMove(this, point);
    }

}

void Unit::attack(Unit &other) {

    for (auto o: observers){
        o->onUnitAttack(this, &other);
    }

}

Unit::~Unit() {

    for (auto o: observers) {
        o->onUnitDestroy(this);
    }

}

void Unit::damage(int damage) {

    for (auto o: observers) {
        o->onUnitDamaged(this);
    }

    if (damage < 0) damage = 0;
    health -= damage;
    if (health <= 0){

        for (auto o: observers) {
            o->onUnitDestroy(this);
        }

    }

}

void Unit::heal(int hp) {

    for (auto o: observers) {
        o->onUnitHeal(this);
    }

    health += hp;

}

Unit &Unit::operator=(const Unit &other) {

    if (&other == this)
        return *this;

    armor = other.armor;
    weapon = other.weapon;
    health = other.health;

    return *this;

}

Unit &Unit::operator<<(NeutralObject *neutralObject) {
    neutralObject->applyTo(*this);
    return *this;
}

Unit::Unit(UnitType unitType, Armor &armor, Weapon &weapon, int health):
GameObject(ObjectType::UNIT),
armor(armor),
weapon(weapon),
health(health)
{}

int Unit::getHealth() {
    return health;
}

void Unit::print(std::ostream &stream) const {

    switch(unitType){

        case UnitType::WIZARD:
            stream << "W";
        case UnitType::ARCHER:
            stream << "A";
        case UnitType::INFANTRY:
            stream << "I";

    }

}