
#include "Unit.h"

Unit::Unit(const Unit &other):
        GameObject(ObjectType::UNIT),
        armor(other.armor),
        weapon(other.weapon),
        health(other.health) {}

void Unit::addObserver(UnitObserver *observer) {

    game::log << "[Unit] observer added" << game::logend;
    observers.push_back(observer);

}

void Unit::move(Point point) {

    for (auto o: observers){
        o->onUnitMove(this, point);
    }
    game::log << "[Unit] moving" << game::logend;

}

void Unit::attack(Unit &other) {

    for (auto o: observers){
        o->onUnitAttack(this, &other);
    }
    game::log << "[Unit] attack" << game::logend;

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

    game::log << "[Unit] damaged by " << damage << " points" << game::logend;

}

void Unit::heal(int hp) {

    for (auto o: observers) {
        o->onUnitHeal(this);
    }

    health += hp;
    game::log << "[Unit] healed by " << hp << " points \n" << game::logend;

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
        unitType(unitType),
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
            break;
        case UnitType::ARCHER:
            stream << "A";
            break;
        case UnitType::INFANTRY:
            stream << "I";
            break;

    }

}