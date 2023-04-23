#pragma once
#include "IUnit.h"

enum class NeutralObject
{
	HOSPITAL,
	ATTACKUPGRADER,
	ARMOURUPGRADER,
	SPIKES,
};

class INeutralObject
{
	virtual NeutralObject getType() = 0;
};

class Hospital : public INeutralObject {
public:
	const int HPToAdd = 20; 
	NeutralObject getType() override;
	friend IUnit& operator+=(IUnit& left, const Hospital& right);
};

class AttackUpgrader: public INeutralObject {
public:
	const int attackToAdd = 10;
	NeutralObject getType() override;
	friend IUnit& operator+=(IUnit& left, const AttackUpgrader& right);
};

class ArmourUpgrader : public INeutralObject {
public:
	const int armourToAdd = 10;
	NeutralObject getType() override;
	friend IUnit& operator+=(IUnit& left, const ArmourUpgrader& right);
};

class Spikes : public INeutralObject {
public:
	const int damage = 25;
	NeutralObject getType() override;
	friend IUnit& operator+=(IUnit& left, const Spikes& right);
};

