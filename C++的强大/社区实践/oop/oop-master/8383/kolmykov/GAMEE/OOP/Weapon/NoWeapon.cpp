#include "NoWeapon.h"



NoWeapon::NoWeapon()
{
	range = 0;
	damage = 0;
}

NoWeapon::NoWeapon(const NoWeapon & other):Weapon(other)
{
}


NoWeapon::~NoWeapon()
{
}
