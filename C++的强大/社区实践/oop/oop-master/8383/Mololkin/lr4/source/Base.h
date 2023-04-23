#pragma once
#include <vector>
#include <utility>
#include <iterator>
#include <vector>
#include <list>
#include <iostream>
#include "IUnit.h"
#include "UnitFañtory.h"
#include "Observer.h"

class Base : public Observer
{
private:
	int health;
	int maxUnitsFromBase;
	int numUnitsFromBase = 0;
	int coordX;
	int coordY;
	int baseNum;
	std::vector<IUnit*> unitsFromBase;
public:
	int countUnits();
	Base(int coordX, int coordY, int baseNum) : coordX(coordX), coordY(coordY), health(1000), maxUnitsFromBase(20), baseNum(baseNum) {};
	int getX();
	int getY();
	int getNumUnitsFromBase();
	int getHealth();
	int getBaseNum();
	void downHP(int numAtack);
	bool checkCreating();
	IUnit* createUnit(Units unitType, std::pair<int, int> possetion);
	void deleteUnit(IUnit* unit);
	void updateNotify(IUnit* unit, Event event) override;
};