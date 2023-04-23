

#include "Base.h"

bool Base::addUnit(Unit *unit, Point position) {
    if (units.size() < maxObjectsCount){

        units.push_back(unit);
        for (auto bo: baseObservers){
            bo->onBaseNewUnitCreated(unit, position);
        }
        return true;

    } else{

        return false;

    }
}

void Base::onUnitAttack(Unit *unit, Unit *other) {
    std::cout << "Base: Unit " << unit << " attack" << std::endl;
}

void Base::onUnitMove(Unit *unit, Point p) {

    std::cout << "Base: Unit " << unit << " moving" << std::endl;

}

void Base::onUnitDestroy(Unit *unit) {

    auto position = std::find(units.begin(), units.end(), unit);
    if (position != units.end()) {
        units.erase(position); // Удаление юнита из принадлежащих к этой базе
        std::cout << "Base: Unit " << unit << " destroyed" << std::endl;
    } else{
        std::cout << "Called observer of base for unit don't belong to it" << std::endl;
    }

}

void Base::onUnitDamaged(Unit *unit) {

    std::cout << "Base: Unit " << unit << " damaged" << std::endl;

}

void Base::onUnitHeal(Unit *unit) {

    std::cout << "Base: Unit " << unit << " healed" << std::endl;

}

void Base::print(std::ostream &stream) const {

    stream << "B";

}

void Base::addObserver(BaseObserver *baseObserver) {

    baseObservers.push_back(baseObserver);

}
