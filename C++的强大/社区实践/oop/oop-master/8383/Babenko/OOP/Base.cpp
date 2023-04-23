#include "Base.h"
bool Base::canAddUnit(Unit *unit, Point position) {
  if (currentUnits.size() < maxObjectsCount) {
    currentUnits.push_back(unit);
    for (auto baseObserver : baseObservers) {
      baseObserver->onBaseNewUnitCreated(unit, position);
    }
    game::log << "[Base] " << *unit << " added";
    return true;
  } else {
    game::log << "[Base] Can't add unit" << game::logend;
    return false;
  }
}

void Base::onUnitAttack(Unit *unit, Unit *other) {
  game::log << "[Base] " << *unit << " is about to attack " << *other << game::logend;
}

void Base::onUnitMoved(Unit *unit, Point p) {
  game::log << "[Base] " << *unit << " is about to move to x: " << p.x << ", y: " << p.y << game::logend;
}

void Base::onUnitDestroyed(Unit *unit) {
  auto position = std::find(currentUnits.begin(), currentUnits.end(), unit);
  if (position != currentUnits.end()) {
    currentUnits.erase(position); // Удаление уничтоженного юнита из принадлежащих к этой базе
    game::log << "[Base] " << *unit << " was destroyed" << game::logend;
  } else {
    game::log << "[Base] Called Base observer for unit doesn't belong to it" << game::logend;
  }
}

void Base::onUnitDamaged(Unit *unit) {
  game::log << "[Base] " << *unit << " was damaged" << game::logend;
}

void Base::onUnitHealed(Unit *unit) {
  game::log << "[Base] " << *unit << " was healed" << game::logend;
}

void Base::print(std::ostream &stream) const {
  stream << "B";
}

void Base::addBaseObserver(BaseObserver *baseObserver) {
  baseObservers.push_back(baseObserver);
  game::log << "[Base] Added Base observer" << game::logend;
}