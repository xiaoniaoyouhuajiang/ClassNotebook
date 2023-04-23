#include "pch.h"
#include "GameUnits.h"
#include "UnitParent.h"
#include "GameUtilities.h"
#include "GameField.h"
#include "GameBases.h"
#include "Logger.h"
#include "MyException.h"
#include <iostream>
#include <algorithm>
#include <fstream>



void GameUnits::updateBorders(Vector2D fieldBorders) {
	borders = fieldBorders;
	for (auto &unit : units) {
		unit->updateLocation(fieldBorders);
	}
}

void GameUnits::switchUnit(bool forward) {
	try {
		if (units.size() == 0) {
			throw ArrayException("Array accsess ERROR!", units.size(), currentUnitIndex);
		}
		units[currentUnitIndex]->unitProps.isActive = false;
		if (forward) {
			currentUnitIndex++;
		} else {
			currentUnitIndex--;
		}
		GameUtilities::clamp(currentUnitIndex, units.size() - 1, 0);
		units[currentUnitIndex]->unitProps.isActive = true;
	} catch (ArrayException &exception) {
		LoggerProxy logger;
		logger.logEvent(new LogEntry(exception.getMes()));
	}
}

bool GameUnits::createUnit(char type, Vector2D location, GameBase *base) {
	if (units.size() < UNITS_MAX) {
		switch (type) {
		case UNIT_L_BEE:
			units.push_back(unitsFactoryLigth.createFlyingUnit(field, this, base));
			break;
		case UNIT_L_FLOWER:
			units.push_back(unitsFactoryLigth.createGroundUnit(field, this, base));
			break;
		case UNIT_L_SPRINKLER:
			units.push_back(unitsFactoryLigth.createSmallUnit(field, this, base));
			break;
		case UNIT_D_FLY:
			units.push_back(unitsFactoryDew.createFlyingUnit(field, this, base));
			break;
		case UNIT_D_COAL:
			units.push_back(unitsFactoryDew.createGroundUnit(field, this, base));
			break;
		case UNIT_D_COLLECTOR:
			units.push_back(unitsFactoryDew.createSmallUnit(field, this, base));
			break;
		default:
			break;
		}

		GameUtilities::clamp(location, borders, Vector2D(0, 0));

		units.back()->unitProps.location = location;
		field->getBlockAtLocation(location)->setUnit(units.back());

		if (units.size() == 1) {
			currentUnitIndex = 0;
			units.back()->unitProps.isActive = true;
		}

		GameUnitAdapter adapterUnit(units.back());
		adapterUnit.logUnitSpawn();

		GameBaseAdapter adapterBase(base);
		adapterBase.logBaseSpawnUnit(units.back());

		return true;
	}

	return false;
}

bool GameUnits::moveUnit(Vector2D direction) {
	try {
		if (currentUnitIndex >= units.size()) {
			throw ArrayException("Array accsess ERROR!", units.size(), currentUnitIndex);
		}
		if (!overlapCheck(units[currentUnitIndex]->unitProps.location + direction) &&
			field->getBlockAtLocation(units[currentUnitIndex]->unitProps.location + direction)->isWalkable) {

			field->getBlockAtLocation(units[currentUnitIndex]->unitProps.location)->setUnit(nullptr);

			units[currentUnitIndex]->move(direction, borders);

			field->getBlockAtLocation(units[currentUnitIndex]->unitProps.location)->setUnit(units[currentUnitIndex]);

			field->onMove(*this);

			return true;
		}

	} catch (ArrayException &exception) {
		LoggerProxy logger;
		logger.logEvent(new LogEntry(exception.getMes()));
	}
	return false;

}

UnitParent *GameUnits::getUnit(Vector2D location) {
	for (auto &unit : units) {
		if (unit->unitProps.location == location) {
			return unit;
		}
	}

	return nullptr;
}

void GameUnits::ereaseUnit(UnitParent *unit) {
	int i;
	for (i = 0; i < units.size(); i++) {
		if (units[i] == unit) {
			break;
		}
	}
	
	field->getBlockAtLocation(units[i]->unitProps.location)->setUnit(nullptr);
	unit = nullptr;

	units.erase(units.begin() + i);
	if (currentUnitIndex >= units.size()) {
		currentUnitIndex = units.size() - 1;
	}
}

GameUnits::GameUnits(Vector2D fieldBorders, GameField *field, GameBasesContainer *bases) : field(field), bases(bases) {
	borders = fieldBorders;
}

GameUnits::GameUnits(std::string unitsFileName, Vector2D fieldBorders) {
	borders = fieldBorders;

	int size;
	char type;
	Vector2D location;
	std::ifstream ifs;
	ifs.open(unitsFileName, std::ifstream::in);
	ifs >> size;

	for (int i = 0; i < size; i++) {
		ifs >> type >> location.x >> location.y;
		//createUnit(type, location);
	}

	units[0]->unitProps.isActive = true;
	currentUnitIndex = 0;

	ifs.close();


}

GameUnits::~GameUnits() {
	units.clear();
}

int GameUnits::overlapCheck(Vector2D targetLocation) {
	UnitParent *unit;
	unit = getUnit(targetLocation);
	if (unit != nullptr) return 1;

	return 0;
}

