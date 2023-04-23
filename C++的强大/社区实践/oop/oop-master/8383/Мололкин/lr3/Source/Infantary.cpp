#include "Infantary.h"



Units Swordsman::getUnitType()
{
	return Units::SWORDSMAN;
}


Units Spearman::getUnitType()
{
	return Units::SPEARMAN;
}

int Infantary::getId()
{
	return id;
}

int Infantary::getHealth()
{
	return health;
}

int Infantary::getArmour()
{
	return armour;
}

int Infantary::getAttack()
{
	return attack;
}

int Infantary::getTeam()
{
	return team;
}

void Infantary::upHP(int num)
{
	this->health += num;
}

void Infantary::upArmour(int num)
{
	this->armour += num;
}

void Infantary::upAttack(int num)
{
	this->attack += num;
}

void Infantary::downHP(int num)
{
	this->health -= num;

}


void Infantary::downArmour(int num)
{
	this->armour -= num;
	if (this->armour < 0) armour = 0;
}