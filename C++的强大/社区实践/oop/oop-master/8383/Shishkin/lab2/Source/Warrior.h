//#pragma once
#ifndef WARRIOR_H
#define WARRIOR_H

#include <iostream>
#include "BaseSubject.h"

//class Subject;
class UnitNum;

class Warrior : public Subject {
public:
	Warrior();
	~Warrior();
	void SetPlaceX(int placex);
	int GetPlaceX(void);
	void SetPlaceY(int placey);
	int GetPlaceY(void);
	void SetValue(std::string value);
	std::string GetValue(void);
	void SetHealth(int health);
	int GetHealth();
	void SetDamage(int damage);
	int GetDamage();
	void SetArmor(int armor);
	int GetArmor();
	void SetAbilityToWalk(int atw);
	int GetAbilityToWalk();
	void attack(Warrior& w2);  //атака на w2
	UnitNum* un;

private:
	int placex;
	int placey;
	std::string value;

	int health;
	int damage;
	int armor;
	int abilityToWalk;   //возможность произвести ход за юнита
};

#endif
