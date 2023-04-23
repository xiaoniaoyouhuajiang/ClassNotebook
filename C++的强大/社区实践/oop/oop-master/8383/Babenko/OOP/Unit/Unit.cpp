#include "Unit.h"

Unit::Unit(const Unit &other) :
    GameObject(ObjectType::UNIT),
    unitType(unitType),
    unitArmor(other.unitArmor),
    unitWeapon(other.unitWeapon),
    unitHealth(other.unitHealth) {}

Unit::Unit(UnitType unitType, Armor &armor, Weapon &weapon, int health) :
    GameObject(ObjectType::UNIT),
    unitType(unitType),
    unitArmor(armor),
    unitWeapon(weapon),
    unitHealth(health) {}

void Unit::addObserver(UnitObserver *observer) {
  unitObservers.push_back(observer);
  game::log << "[Unit] Unit observer added" << game::logend;
}

void Unit::move(Point point) {
  for (auto observer : unitObservers) {
    observer->onUnitMoved(this, point);
  }
}

void Unit::attack(Unit &other) {
  for (auto observer: unitObservers) {
    observer->onUnitAttack(this, &other);
  }
}

Unit::~Unit() {
  for (auto observer : unitObservers) {
    observer->onUnitDestroyed(this);
  }
}

void Unit::damage(int damage) {

  for (auto observer : unitObservers) {
    observer->onUnitDamaged(this);
  }

  unitHealth -= std::max(damage, 0);
  if (unitHealth <= 0) {
    for (auto observer : unitObservers) {
      observer->onUnitDestroyed(this);
    }
    unitHealth = 0;
  }
}

void Unit::heal(int healingPoints) {

  for (auto observer : unitObservers) {
    observer->onUnitHealed(this);
  }

  unitHealth += healingPoints;
}

Unit &Unit::operator=(const Unit &other) {

  if (this == &other)
    return *this;

  unitArmor = other.unitArmor;
  unitWeapon = other.unitWeapon;
  unitHealth = other.unitHealth;

  return *this;

}

Unit &Unit::operator<<(NeutralObject *neutralObject) {
  neutralObject->applyTo(*this);
  return *this;
}

int Unit::getUnitHealth() {
  return unitHealth;
}

void Unit::print(std::ostream &stream) const {
  switch (unitType) {
    case UnitType::WIZARD:stream << "W";break;
    case UnitType::ARCHER:stream << "A";break;
    case UnitType::VIKING:stream << "V";break;
    case UnitType ::UNKNOWN:break;
  }
}