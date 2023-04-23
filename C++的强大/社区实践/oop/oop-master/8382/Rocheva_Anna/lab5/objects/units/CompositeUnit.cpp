#include "CompositeUnit.hpp"

void CompositeUnit::printUnits() {
    std::cout << "Units:" << std::endl;
    for (auto & unit : units){
        std::cout << "(" << unit->getCoordinates()->x << "," << unit->getCoordinates()->y << ") = " << unit->getName() << std::endl;
    }

}

void CompositeUnit::deleteUnit(Unit *unit) {

    int ind = 0;
    for (auto & un : units) {
        if (unit == un){
            units.erase(units.begin() + ind);
            return;;
        }
        ind++;
    }

}
