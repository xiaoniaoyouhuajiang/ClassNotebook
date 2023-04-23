#include "Mechanisms.h"

Units Ballista::getUnitType()
{
	return Units::BALLISTA;
}


Units Catapult::getUnitType()
{
	return Units::CATAPULT;
}

int Mechanisms::getId()
{
	return id;
}

int Mechanisms::getHealth()
{
	return health;
}

int Mechanisms::getArmour()
{
	return armour;
}

int Mechanisms::getAttack()
{
	return attack;
}

int Mechanisms::getTeam()
{
	return team;
}

void Mechanisms::upHP(int num)
{
	this->health += num;
}

void Mechanisms::upArmour(int num)
{
	this->armour += num;
}

void Mechanisms::upAttack(int num)
{
	this->attack += num;
}

void Mechanisms::downHP(int num)
{
	this->health -= num;
}

void Mechanisms::downArmour(int num)
{
	this->armour -= num;
	if (this->armour < 0) armour = 0;
}
