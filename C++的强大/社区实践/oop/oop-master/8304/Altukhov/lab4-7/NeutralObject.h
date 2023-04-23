#pragma once
#include "INeutralObject.h"
#include "Strategy.h"
#include "TowerStrategy.h"
#include "ShrineStrategy.h"
#include "CannonStrategy.h"
#include "WeaponryStrategy.h"
enum class NeutralObjectTypes {
	TOWER, WEAPONRY, CANNON, SHRINE
};

class NeutralObject :public INeutralObject {

	NeutralObjectTypes type;
	Strategy* strategy;

public:

	NeutralObject() = default;
	~NeutralObject() = default;
	NeutralObjectTypes getNeutralObjectType();
	void setNeutralObjectType(NeutralObjectTypes type);
	void applyEffect(Unit*& unit);
	void removeEffect(Unit*& unit);
	void selectStrategy();
	
};

void operator<<(Unit& unit, Strategy* strategy);