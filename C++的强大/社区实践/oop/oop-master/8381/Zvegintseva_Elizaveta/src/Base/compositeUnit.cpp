#include "compositeUnit.h"


void CompositeUnit::addUnit(Unit *unit)
{
    units.push_back(unit);
}

bool CompositeUnit::delUnit(Subject *unit)
{
    for(std::vector<Unit*>::iterator iter = units.begin(); iter != units.end(); iter++){
        if (*iter == unit){
            units.erase(iter);
            return true;
        }
    }
    return false;
}

string CompositeUnit::getName()
{
    string names{};
    for(Unit* u : units){
        if(u == units.back()){
            names.append(u->getName());
        }else{
            names.append("\n");
        }
    }
    return names;
}

Unit *CompositeUnit::copyItem()
{
    return new CompositeUnit(*this);
}

string CompositeUnit::characteristic()
{
    string characteristic{};
    for(Unit* u : units){
        if(u == units.back()){
            characteristic.append(u->getName());
        }else{
            characteristic.append("\n");
        }
    }
    return characteristic;
}

Attributes *CompositeUnit::getAttributes() const
{
    size_t health = 0;
    size_t armor = 0;
    size_t attack = 0;
    for(Unit* u : units){
        health += static_cast<size_t>(u->getAttributes()->getHealth());
        armor += static_cast<size_t>(u->getAttributes()->getArmor());
        attack += static_cast<size_t>(u->getAttributes()->getAttack());
    }
    attributes->setAllAttributes(static_cast<int>(health), static_cast<int>(armor), static_cast<int>(attack));
    return attributes;
}

void CompositeUnit::move(int x, int y)
{
    for(Unit* u : units){
        u->move(x, y);
    }
}

Unit *CompositeUnit::getUnit(int x) const
{
    return units.at(x);
}

UnitsType CompositeUnit::getTypeEnum() const
{
    return COMPOSITEUNITS;
}

vector<Unit *> CompositeUnit::getUnits() const
{
    return units;
}
