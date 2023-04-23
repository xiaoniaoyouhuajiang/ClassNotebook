#pragma once
#include <vector>
#include <iostream>

class Hospital;
class ArmourUpgrader;
class Spikes;
class AttackUpgrader;


enum class Units
{
	SPEARMAN,
	SWORDSMAN,
	ARCHER,
	BALLISTA,
	CROSSBOWMAN,
	CATAPULT,

};

class IUnit
{
public:
	virtual Units getUnitType() = 0;
	virtual int getHealth() = 0;
	virtual int getArmour() = 0;
	virtual int getAttack() = 0;
	virtual int getId() = 0;
	virtual int getTeam() = 0;
	virtual void upHP(int num) = 0;
	virtual void upArmour(int num) = 0;
	virtual void upAttack(int num) = 0;
	virtual void downHP(int num) = 0;
	virtual void downArmour(int num) = 0;
	static std::string retrunUnitTypeString(Units type);
private:
	friend IUnit& operator+=(IUnit& left, const Hospital& right);
	friend IUnit& operator+=(IUnit& left, const AttackUpgrader& right);
	friend IUnit& operator+=(IUnit& left, const ArmourUpgrader& right);
	friend IUnit& operator+=(IUnit& left, const Spikes& right);
};

