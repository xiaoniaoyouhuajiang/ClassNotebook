//
// Created by Artem Butko on 15/05/2020.
//

#include "UnitComposite.h"

UnitComposite::UnitComposite()
{
    this->id = 'G';
}

void UnitComposite::addUnit(Object *unit)
{
    composite.push_back(unit);
}

void UnitComposite::deleteUnit(Object *unit)
{
    for(auto it = composite.begin(); it != composite.end(); )
    {
        if(*it == unit) composite.erase(it);
        else ++it;
    }
}

void UnitComposite::getInformation()
{
    std::cout << "TOTAL:                               " << composite.size() << std::endl;
    std::cout << "UNITS: ";
    for(auto i : composite) std::cout << i->id << " ";
}



