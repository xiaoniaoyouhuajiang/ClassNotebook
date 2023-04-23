#include "weapon.h"

GetWeapon::GetWeapon(Weapon * wep):weapon(wep)
{

}

void GetWeapon::operator +=(Unit &unit)
{
    weapon->use(unit);
}

string GetWeapon::getType()const{
    return "neutral";
}

GetWeapon::~GetWeapon()
{
    delete weapon;
}

void Sword::use(Unit &unit)
{
    unit.getAttributes()->setAttack(unit.getAttributes()->getAttack()+50);
}

void Hatchet::use(Unit &unit)
{
    unit.getAttributes()->setAttack(unit.getAttributes()->getAttack()+100);
}


string GetWeapon::characteristic()
{
    return "GetWeapon";
}
