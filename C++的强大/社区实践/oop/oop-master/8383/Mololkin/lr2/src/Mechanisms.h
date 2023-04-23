#pragma once
#include <iostream>
#include "IUnit.h"

class Mechanisms : public IUnit
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
	Mechanisms(int id, int health, int armour, int attack) : id(id), health(health), armour(armour), attack(attack) {}

};

class Ballista : public Mechanisms
{
public:
	const int maxMove = 1;
	Ballista(int id) : Mechanisms(id, 90, 130, 0) {};
	Ballista(Ballista& other) : Mechanisms(other.id, other.health, other.armour, other.attack) {};
	Units getUnitType() override;
};

class Catapult : public Mechanisms
{
public:
	const int maxMove = 1;
	Catapult(int id) : Mechanisms(id, 90, 130, 0) {};
	Catapult(Catapult& other) : Mechanisms(other.id, other.health, other.armour, other.attack) {};
	Units getUnitType() override;
};