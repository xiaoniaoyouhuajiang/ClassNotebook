#include "Grenade.h"



Grenade::Grenade()
{
	range = 3;
	damage = 150;
}

Grenade::Grenade(const Grenade & other):Weapon(other) {

}


Grenade::~Grenade()
{
}
