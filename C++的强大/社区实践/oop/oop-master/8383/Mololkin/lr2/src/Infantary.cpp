#include "Infantary.h"


//Swordsman::Swordsman(int id)
//{
//	this->id = id;
//	this->health= 45;
//	this->attack = 30;
//	this->armour = 90;
//}

//Swordsman::Swordsman(Swordsman& other)
//{
//	this->id = other.id;
//	this->health = (other.health);
//	this->attack = (other.attack);
//	this->armour = (other.armour);
//}

Units Swordsman::getUnitType()
{
	return Units::SWORDSMAN;
}

//Spearman::Spearman(int id)
//{
//	this->id = id;
//	this->health = 90;
//	this->attack = 130;
//	this->armour = 0;
//}

//Spearman::Spearman(Spearman& other)
//{
//	this->id = other.id;
//	this->health = (other.health);
//	this->attack = (other.attack);
//	this->armour = (other.armour);
//}

Units Spearman::getUnitType()
{
	return Units::SPEARMAN;
}

int Infantary::getId()
{
	return id;
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
