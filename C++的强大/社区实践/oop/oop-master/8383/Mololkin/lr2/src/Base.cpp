#include "Base.h"


int Base::getX()
{
	return coordX;
}

int Base::getY()
{
	return coordY;
}

bool Base::checkCreating()
{
	if (numUnitsFromBase + 1 > maxUnitsFromBase) return true;
	return false;
}

IUnit* Base::createUnit(Units unitType, std::pair<int, int> possetion) {
	IUnit* createdUnit = UnitFañtory::createUnit(unitType);
	if (numUnitsFromBase < maxUnitsFromBase) {
		unitsFromBase.push_back(createdUnit);
		numUnitsFromBase++;
	}
	return createdUnit;
}

void Base::deleteUnit(IUnit* unit)
{
	for (auto iter = unitsFromBase.begin(); iter != unitsFromBase.end(); ++iter) {
		if (*iter == unit) {
			unitsFromBase.erase(iter);
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
