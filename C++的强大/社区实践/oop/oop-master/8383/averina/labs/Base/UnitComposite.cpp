

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
    std::cout << "Total:                               " << composite.size() << std::endl;
    std::cout << "Units: " << std::endl;
    for(auto i : composite) std::cout << i->id << ": (" << i->x << "," << i->y << "); hp: " << i->health.get() << "; dmg/r/cost: " << i->damage.getDamage() << "/" << damage.getRange() << "/" << damage.getCost() << "; mp: " << i->mana.get()<< std::endl;
}
