#include "Base.h"

int Base::getX()
{
	return coordX;
}

int Base::getY()
{
	return coordY;
}

int Base::getNumUnitsFromBase()
{
	return numUnitsFromBase;
}

int Base::getHealth()
{
	return health;
}

int Base::getBaseNum()
{
	return baseNum;
}

void Base::downHP(int numAtack)
{
	this->health -= numAtack;
}

bool Base::checkCreating()
{
	if (numUnitsFromBase + 1 < maxUnitsFromBase) return true;
	return false;
}

IUnit* Base::createUnit(Units unitType, std::pair<int, int> possetion) {
	IUnit* createdUnit = UnitFañtory::createUnit(unitType, baseNum);
	if (numUnitsFromBase < maxUnitsFromBase) {
		unitsFromBase.push_back(createdUnit);
		
		numUnitsFromBase++;
	}
	return createdUnit;
}


int Base::countUnits()
{
	int result = 0;
	for (unsigned int i = 0; i < unitsFromBase.size(); i++) {
		if (unitsFromBase[i] != nullptr) result++;
	}
	return result;
}

void Base::deleteUnit(IUnit* unit)
{
	for (auto iter = unitsFromBase.begin(); iter < unitsFromBase.end(); iter++) {
		if (*iter == unit) {
			numUnitsFromBase--;
			*iter = nullptr;
		}
	}
}



void Base::updateNotify(IUnit* unit, Event event)
{
	if (event == Event::UNIT_CREATE) {

		unitsFromBase.push_back(unit);

	}
	else {
		deleteUnit(unit);
	}

}
