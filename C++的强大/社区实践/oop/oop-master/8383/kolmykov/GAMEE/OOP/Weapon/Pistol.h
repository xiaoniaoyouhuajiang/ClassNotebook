#pragma once
#include "Weapon.h"
class Pistol :
	public Weapon
{
public:
	Pistol();
	Pistol(const Pistol& other);
	~Pistol();
};

