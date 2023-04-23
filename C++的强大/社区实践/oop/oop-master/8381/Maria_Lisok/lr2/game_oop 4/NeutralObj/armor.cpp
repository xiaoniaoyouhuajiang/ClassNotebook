#include "armor.h"

GetArmor::GetArmor(Armor* a) : armor(a)
{

}

void GetArmor::operator +=(Unit &unit)
{
    armor->use(unit);
}
string GetArmor::getType()const{
    return "neutral";
}
GetArmor::~GetArmor()
{
    delete armor;
}


string GetArmor::characteristic()
{
    return "GetArmor";
}

void Helmet::use(Unit &unit)
{
    unit.getAttributes()->setArmor(unit.getAttributes()->getArmor()+20);
}

void Mittens::use(Unit &unit)
{
    unit.getAttributes()->setArmor(unit.getAttributes()->getArmor()+40);
}

void Sabaton::use(Unit &unit)
{
    unit.getAttributes()->setArmor(unit.getAttributes()->getArmor()+60);
}



