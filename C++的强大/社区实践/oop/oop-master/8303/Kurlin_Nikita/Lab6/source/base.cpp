#include "base.h"

Base::Base(int maxUnitsCount, int health, int xx, int yy, int baseNumb) : baseNumb(baseNumb), unitCount(0), maxCount(maxUnitsCount), unitCurr(0),
    health(health), x(xx), y(yy)
{
    units = new CompositeUnit();
}

Unit* Base::createUnit(std::string unitName)
{
        Unit* unit = nullptr;
        if (unitName == "Flatbow"){
            unit = ArchersFactory().createWeak();
        }
        else if (unitName == "Longbow"){
            unit = ArchersFactory().createStrong();
        }
        else if (unitName == "Dragoon"){
            unit = CavalryFactory().createStrong();
        }
        else if (unitName == "Hussar"){
            unit = CavalryFactory().createWeak();
        }
        else if (unitName == "Swordsman"){
            unit = InfantryFactory().createStrong();
        }
        else if (unitName == "Spearman"){
            unit = InfantryFactory().createWeak();
        }

        units->addUnit(unit);
        unitCount++;
        return unit;
}

void Base::deleteUnit(Subject *unit)
{
    if (units->deleteUnit(unit)){
        unitCount--;
    }
}

int Base::getCapacityCount()
{
    return maxCount - unitCount;
}

Unit* Base::getCurrUnit()
{
    if (unitCurr >= units->unitsMas.size())
        unitCurr = 0;
    return units->unitsMas[unitCurr++];
}

int Base::getX()
{
    return this->x;
}

int Base::getY()
{
    return this->y;
}

int Base::getCount()
{
    return this->unitCount;
}

int Base::getHealth()
{
    return this->health;
}

bool Base::getDamage(int numb)
{
    this->health -= numb;
    if (this->health <= 0){
        this->health = 0;
        LoggerProxy::baseDestruction(this);
        return true;
    }
    LoggerProxy::baseDamage(this);
    return false;
}
