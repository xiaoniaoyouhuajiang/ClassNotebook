#include "Pistol.h"



Pistol::Pistol()
{
	range = 5;
	damage = 120;
}

Pistol::Pistol(const Pistol & other):Weapon(other)
{
}


Pistol::~Pistol()
{
}
