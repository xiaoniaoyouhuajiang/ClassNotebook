#pragma once
#include <vector>
#include <utility>
#include <iterator>
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
	std::vector<IUnit*> unitsFromBase;
public:
	Base(int coordX, int coordY) : coordX(coordX), coordY(coordY), health(100), maxUnitsFromBase(20) {};
	int getX();
	int getY();
	bool checkCreating();
	IUnit* createUnit(Units unitType, std::pair<int, int> possetion);
	void deleteUnit(IUnit* unit);
	void updateNotify(IUnit* unit, Event event) override;
};