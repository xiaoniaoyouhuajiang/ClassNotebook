#include "unitsgroup.h"

void UnitsGroup::addUnit(Unit *unit) {
    unitsGroup.push_back(unit);
}
void UnitsGroup::removeUnit(Unit *unit) {
    for(auto it = unitsGroup.begin(); it!=unitsGroup.end(); ) {
        if(*it == unit)
            unitsGroup.erase(it);
        else {
            ++it;
        }
    }
}

void UnitsGroup::print() {
    for(size_t i=0;i<unitsGroup.size();i++) {
        std::cout << i << "\t";
        unitsGroup[i]->print();
        std::cout << std::endl;
    }
    std::cout << std::endl;
}