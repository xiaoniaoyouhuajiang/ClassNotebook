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

NeutralType GetArmor::getTypeEnum()
{
    return armor->type();
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

NeutralType Helmet::type()
{
    return HELMET;
}

void Mittens::use(Unit &unit)
{
    unit.getAttributes()->setArmor(unit.getAttributes()->getArmor()+40);
}

NeutralType Mittens::type()
{
    return MITTENS;
}

void Sabaton::use(Unit &unit)
{
    unit.getAttributes()->setArmor(unit.getAttributes()->getArmor()+60);
}

NeutralType Sabaton::type()
{
    return SABATON;
}



