#include "Bat.h"



Bat::Bat()
{
	range = 1;
	damage = 80;
}

Bat::Bat(const Bat & other):Weapon(other)
{
}


Bat::~Bat()
{
}
