#pragma once
#include <iostream>
#include "IUnit.h"

class Shooter : public IUnit 
{
protected:
	int id;
	int health;
	int armour;
	int attack;

public:
	int getId() override;
	void upHP(int num) override;
	void upArmour(int num) override;
	void upAttack(int num) override;
	void downHP(int num)override;
	void downArmour(int num) override;
	Shooter(int id, int health, int armour, int attack) : id(id), health(health), armour(armour), attack(attack) {}

};

class Archer : public Shooter {
public:
	const int maxMove = 2;
	Archer(int id) : Shooter(id, 90, 130, 0) {};
	Archer(Archer& other) : Shooter(other.id, other.health, other.armour, other.attack) {};
	Units getUnitType() override;
};

class Crossbowman : public Shooter {
public:
	const int maxMove = 1;
	Crossbowman(int id) : Shooter(id, 90, 130, 0) {};
	Crossbowman(Crossbowman& other) : Shooter(other.id, other.health, other.armour, other.attack) {};
	Units getUnitType() override;
};

