#include "Shooters.h"

//Archer::Archer(int id)
//{	
//	this->id = id;
//	this->health = 45;
//	this->attack = 30;
//	this->armour = 10;
//}
//
//Archer::Archer(Archer& other)
//{
//	this->id = other.id;
//	this->health = (other.health);
//	this->attack = (other.attack);
//	this->armour = (other.armour);
//}

Units Archer::getUnitType()
{
	return Units::ARCHER;
}

//Crossbowman::Crossbowman(int id)
//{
//	this->id = id;
//	this->health = 45;
//	this->attack = 130;
//	this->armour = 20;
//}
//
//Crossbowman::Crossbowman(Crossbowman& other)
//{
//	this->id = other.id;
//	this->health = (other.health);
//	this->attack = (other.attack);
//	this->armour = (other.armour);
//}

Units Crossbowman::getUnitType()
{
	return Units::CROSSBOWMAN;
}

int Shooter::getId()
{
	return id;
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
