#include "Shooters.h"



Units Archer::getUnitType()
{
	return Units::ARCHER;
}


Units Crossbowman::getUnitType()
{
	return Units::CROSSBOWMAN;
}

int Shooter::getId()
{
	return id;
}

int Shooter::getHealth()
{
	return health;
}

int Shooter::getArmour()
{
	return armour;
}

int Shooter::getAttack()
{
	return attack;
}

int Shooter::getTeam()
{
	return team;
}

void Shooter::upHP(int num)
{
	this->health += num;
}

void Shooter::upArmour(int num)
{
	this->armour += num;
}

void Shooter::upAttack(int num)
{
	this->attack += num;
}

void Shooter::downHP(int num)
{
	this->health -= num;
}

void Shooter::downArmour(int num)
{
	this->armour -= num;
	if (this->armour < 0) armour = 0;
}
