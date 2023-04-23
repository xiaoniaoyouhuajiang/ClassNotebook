#pragma once
#include "Unit.h"

class AbstractFactory
{
public:
	AbstractFactory() {};
	virtual Unit* createDivisionA() = 0;
	virtual Unit* createDivisionB() = 0;
	~AbstractFactory() {};
};


class WarriorsFactory : public AbstractFactory
{
public:
	WarriorsFactory() {};
	Warrior* createDivisionA() {
		return new Swordman;
	}
	Warrior* createDivisionB() {
		return new Spearman;
	}
	~WarriorsFactory() {};
};


class ArchersFactory : public AbstractFactory
{
public:
	ArchersFactory() {};
	Archer* createBowman() {
		return new Bowman;
	}
	Archer* createSlinger() {
		return new Slinger;
	}
	~ArchersFactory() {};
};

class CavalryFactory : public AbstractFactory
{
public:
	CavalryFactory() {};
	Cavalry* createLightCavalry() {
		return new LightCavalry;
	}
	Cavalry* createHeavyCavalry() {
		return new HeavyCavalry;
	}
	~CavalryFactory() {};
	
};
