#pragma once
#include "Weapon.h"
class NoWeapon :
	public Weapon
{
public:
	NoWeapon();
	NoWeapon(const NoWeapon& other);
	~NoWeapon();
};

