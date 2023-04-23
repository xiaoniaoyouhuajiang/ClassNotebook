#include "compositeunit.h"

CompositeUnit::CompositeUnit()
{

}

void CompositeUnit::addUnit(Unit *unit)
{
     unitsMas.push_back(unit);
}

bool CompositeUnit::deleteUnit(Subject *unit)
{
    for(std::vector<Unit*>::iterator iter = unitsMas.begin(); iter != unitsMas.end(); iter++){
        if (*iter == unit){
            unitsMas.erase(iter);
            return true;
        }
    }
    return false;
}

void CompositeUnit::printAll()
{
    for(std::vector<Unit*>::iterator iter = unitsMas.begin(); iter != unitsMas.end(); iter++){
        std::cout << (*iter)->getArmyType() << std::endl;
        //std::cout << (*iter)->attributes->health << std::endl;
    }
}
