#include "Mechanisms.h"

//Ballista::Ballista(int id)
//{
//	this->id = id;
//	this->health = 45;
//	this->attack = 30;
//	this->armour = 10;
//}

//Ballista::Ballista(Ballista& other)
//{
//	this->id = other.id;
//	this->health = (other.health);
//	this->attack = (other.attack);
//	this->armour = (other.armour);
//}

Units Ballista::getUnitType()
{
	return Units::BALLISTA;
}

//Catapult::Catapult(int id)
//{
//	this->id = id;
//	this->health = 90;
//	this->attack = 130;
//	this->armour = 0;
//}

//Catapult::Catapult(Catapult& other)
//{
//	this->id = other.id;
//	this->health = (other.health);
//	this->attack = (other.attack);
//	this->armour = (other.armour);
//}

Units Catapult::getUnitType()
{
	return Units::CATAPULT;
}

int Mechanisms::getId()
{
	return id;
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
