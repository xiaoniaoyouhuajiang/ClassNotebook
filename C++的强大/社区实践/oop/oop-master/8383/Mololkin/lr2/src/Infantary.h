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
public:
	int getId() override;
	void upHP(int num) override;
	void upArmour(int num) override;
	void upAttack(int num) override;
	void downHP(int num) override;
	void downArmour(int num) override;
	Infantary(int id, int health, int armour, int attack) : id(id), health(health), armour(armour), attack(attack) {};
};

class Swordsman : public Infantary {
public:
	const int maxMove = 2;
	Swordsman(int id) : Infantary(id, 45, 30, 90) {};
	Swordsman(Swordsman& other) : Infantary(other.id, other.health, other.armour, other.attack) {};
	Units getUnitType() override;
};

class Spearman : public Infantary {
public:
	const int maxMove = 3;
	Spearman(int id) : Infantary(id, 90, 130, 0) {};
	Spearman(Spearman& other) : Infantary(other.id, other.health, other.armour, other.attack) {};
	Units getUnitType() override;
	void print() {
		std::cout << health << " " << armour << " " << attack << std::endl;
	}
};

