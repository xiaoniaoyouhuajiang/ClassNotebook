#include <iostream>
#include "CompositUnit.h"


void CompositUnit::addUnit(Unit* unit) {
    masUnit.push_back(unit);
}

bool CompositUnit::removeUnit(Unit *unit) {
    std::vector<Unit*>::iterator iter = masUnit.begin();
    while(iter != masUnit.end()){
        if (*iter == unit){
            masUnit.erase(iter);
            return true;
        }
        iter++;
    }
    return false;

}

void CompositUnit::printUnit() {
    std::vector<Unit*>::iterator iter = masUnit.begin();
    while(iter != masUnit.end()){
        std::cout << (*iter)->character<<std::endl;
        iter++;
    }
}