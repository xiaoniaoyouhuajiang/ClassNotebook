//
// Created by shenk on 01.03.2020.
//

#include "Base.h"

bool Base::addUnit(Unit *unit, Point position) {
    if (units.size() < maxObjectsCount){

        units.push_back(unit);
        for (auto bo: baseObservers){
            bo->onBaseNewUnitCreated(unit, position);
        }
        game::log << "[Base] Unit added";
        return true;

    } else{

        game::log << "[Base] Can't add unit" << game::logend;
        return false;

    }
}

void Base::onUnitAttack(Unit *unit, Unit *other) {
    game::log << "[Base]" << *unit << " attack\n";
}

void Base::onUnitMove(Unit *unit, Point p) {

    game::log << "[Base] " << *unit << " moving" << game::logend;

}

void Base::onUnitDestroy(Unit *unit) {

    auto position = std::find(units.begin(), units.end(), unit);
    if (position != units.end()) {
        units.erase(position); // Удаление юнита из принадлежащих к этой базе
        game::log << "[Base] " << *unit << " destroyed" << game::logend;
    } else{
        game::log << "Called observer of base for unit don't belong to it" << game::logend;
    }

}

void Base::onUnitDamaged(Unit *unit) {

    game::log << "[Base] " << *unit << " damaged" << game::logend;

}

void Base::onUnitHeal(Unit *unit) {

    game::log << "[Base] " << *unit << " healed" << game::logend;

}

void Base::print(std::ostream &stream) const {

    stream << "B";

}

void Base::addObserver(BaseObserver *baseObserver) {

    baseObservers.push_back(baseObserver);
    game::log << "[Base] added observer" << game::logend;

}
