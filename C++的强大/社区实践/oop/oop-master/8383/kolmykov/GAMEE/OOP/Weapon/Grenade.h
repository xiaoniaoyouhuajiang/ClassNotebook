#pragma once
#include "Weapon.h"
class Grenade :
	public Weapon
{
public:
	Grenade();
	Grenade(const Grenade& other);
	~Grenade();
};

