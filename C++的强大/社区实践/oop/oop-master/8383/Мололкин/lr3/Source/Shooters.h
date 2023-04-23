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
	int team;

public:
	int getId() override;
	int getHealth() override;
	int getArmour() override;
	int getAttack() override;
	int getTeam() override;
	void upHP(int num) override;
	void upArmour(int num) override;
	void upAttack(int num) override;
	void downHP(int num)override;
	void downArmour(int num) override;
	Shooter(int id, int health, int armour, int attack, int team) : id(id), health(health), armour(armour), attack(attack), team(team) {}

};

class Archer : public Shooter {
public:
	const int maxMove = 2;
	Archer(int id, int team) : Shooter(id, 90, 130, 25, team) {};
	Archer(Archer& other) : Shooter(other.id, other.health, other.armour, other.attack, other.team) {};
	Units getUnitType() override;
};

class Crossbowman : public Shooter {
public:
	const int maxMove = 1;
	Crossbowman(int id, int team) : Shooter(id, 90, 130, 35, team) {};
	Crossbowman(Crossbowman& other) : Shooter(other.id, other.health, other.armour, other.attack, other.team) {};
	Units getUnitType() override;
};

