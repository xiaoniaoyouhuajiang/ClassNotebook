#pragma once
#include <iostream>
#include "IUnit.h"

class Infantary : public IUnit
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
	void downHP(int num) override;
	void downArmour(int num) override;
	Infantary(int id, int health, int armour, int attack, int team) : id(id), health(health), armour(armour), attack(attack), team(team) {};
};

class Swordsman : public Infantary {
public:
	const int maxMove = 2;
	Swordsman(int id, int team) : Infantary(id, 45, 30, 90, team) {};
	Swordsman(Swordsman& other) : Infantary(other.id, other.health, other.armour, other.attack, other.team) {};
	Units getUnitType() override;
};

class Spearman : public Infantary {
public:
	const int maxMove = 3;
	Spearman(int id, int team) : Infantary(id, 90, 130,50, team) {};
	Spearman(Spearman& other) : Infantary(other.id, other.health, other.armour, other.attack, other.team) {};
	Units getUnitType() override;
};

