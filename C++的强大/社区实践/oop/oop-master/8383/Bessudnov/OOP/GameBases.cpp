#include "pch.h"
#include "GameBases.h"
#include "GameUtilities.h"
#include "GameField.h"
#include "UnitParent.h"
#include "Logger.h"
#include "MyException.h"


void GameBasesContainer::setBaseType(GameBaseTypes baseType, int index, GameUnits *gameUnits) {
	switch (baseType) {
	case GameBaseTypes::Zero:
		bases[index] = new DefaultBase(gameUnits);
		break;
	case GameBaseTypes::One:
		bases[index] = new OneBase(gameUnits);
		break;
	case GameBaseTypes::Two:
		bases[index] = new TwoBase(gameUnits);
		break;
	case GameBaseTypes::Three:
		bases[index] = new ThreeBase(gameUnits);
		break;
	case GameBaseTypes::Four:
		bases[index] = new FourBase(gameUnits);
		break;
	}
	GameBaseAdapter adapter(bases.at(index));
	adapter.logBaseSpawn();
}

void GameBasesContainer::switchBase(bool forward) {
	try {
		if (bases.size() <= currentBaseIndex) {
			throw ArrayException("Array accsess ERROR!", bases.size(), currentBaseIndex);
		}
		bases[currentBaseIndex]->isActive = false;
		if (forward) {
			currentBaseIndex++;
		} else {
			currentBaseIndex--;
		}

		GameUtilities::clamp(currentBaseIndex, bases.size() - 1, 0);
		bases[currentBaseIndex]->isActive = true;
	} catch (ArrayException &exception) {
		LoggerProxy logger;
		logger.logEvent(new LogEntry(exception.getMes()));
	}
	
}

UnitParent *GameBasesContainer::spawnUnit(int type) {
	try {
		if (bases.size() <= currentBaseIndex) {
			throw ArrayException("Array accsess ERROR!", bases.size(), currentBaseIndex);
		}
		switch (type) {
		case '1':
			return bases[currentBaseIndex]->spawnCollector();
		case '2':
			return bases[currentBaseIndex]->spawnSprinkler();
		case '3':
			return bases[currentBaseIndex]->spawnU1();
		case '4':
			return bases[currentBaseIndex]->spawnU2();
		case '5':
			return bases[currentBaseIndex]->spawnU3();
		default:
			break;
		}

	} catch (ArrayException &exception) {
		LoggerProxy logger;
		logger.logEvent(new LogEntry(exception.getMes()));
	}
	return nullptr;

}

void GameBasesContainer::spawnDefaultBase(GameUnits *units, float position) {
	bases.push_back(new DefaultBase(units));

	Vector2D baseLoc(field->fieldProps.dimensions.x / 2, (field->fieldProps.dimensions.y - 1) * position);
	bases.back()->location = baseLoc;
	bases.back()->isActive = true;
	currentBaseIndex = 0;

	field->getBlockAtLocation(baseLoc)->setBase(bases.back());
}

GameBase *GameBasesContainer::getBaseAtLocation(Vector2D loc) {
	for (auto &base : bases) {
		if (base->location == loc) return base;
	}
	return nullptr;
}

GameBasesContainer::GameBasesContainer(GameField *field) : field(field) {
}

GameBasesContainer::GameBasesContainer(GameField &field, GameUnits &units) {
	bases.push_back(new DefaultBase(&units));
	bases.back()->location.x = field.fieldProps.dimensions.x / 2;
	bases.back()->location.y = field.fieldProps.dimensions.y - 1;
	bases.back()->isActive = true;
	currentBaseIndex = 0;
}


GameBasesContainer::~GameBasesContainer() {
	for (auto &base : bases) {
		delete base;
	}
}

GameBasesContainer & GameBasesContainer::operator=(const GameBasesContainer &gameBasesContainer) {
	if (&gameBasesContainer == this) {
		return *this;
	}

	currentBaseIndex = gameBasesContainer.currentBaseIndex;

	std::copy(gameBasesContainer.bases.begin(), gameBasesContainer.bases.end(), bases.begin());

	return *this;
}


GameBase::GameBase() {
	unitsCount = 0;
	baseUnits.resize(2); 
	baseUnits[0]->setSize(2);
	baseUnits[1]->setSize(3);
}

GameBase::GameBase(GameUnits *units){
	unitsCount = 0;
	this->units = units;
	baseUnits.resize(2);
	for (auto &units : baseUnits) {
		units = new CompositeUnit;
	}
	baseUnits[0]->setSize(2);
	baseUnits[1]->setSize(3);
}

GameBase::GameBase(const GameBase *gameBase, GameUnits *gameUnits) : GameBase(gameUnits) {
	dew = gameBase->dew;
	ligth = gameBase->ligth;
	isActive = gameBase->isActive;
	type = gameBase->type;
	location = gameBase->location;
	unitType01 = gameBase->unitType01;
	unitType02 = gameBase->unitType02;
	unitType03 = gameBase->unitType03;
	std::copy(gameBase->baseUnits.begin(), gameBase->baseUnits.end(), baseUnits.begin());
}

UnitParent *GameBase::spawnU1() {
	if (baseUnits[1]->units[0] == nullptr) {
		return baseUnits[1]->units[0] = spawnUnit(unitType01);
	}
	return nullptr;
}

UnitParent *GameBase::spawnU2() {
	if (baseUnits[1]->units[1] == nullptr) {
		return baseUnits[1]->units[1] = spawnUnit(unitType02);
	}
	return nullptr;
}

UnitParent *GameBase::spawnU3() {
	if (baseUnits[1]->units[2] == nullptr) {
		return baseUnits[1]->units[2] = spawnUnit(unitType03);
	}
	return nullptr;
}

UnitParent *GameBase::spawnCollector() {
	if (baseUnits[0]->units[0] == nullptr) {
		if (units->createUnit(UNIT_D_COLLECTOR, Vector2D(location.x - 1, location.y - 1), this)) {
			baseUnits[0]->units[0] = units->units.back();
			unitsCount++;
			return baseUnits[0]->units[0];
		}
	}
	return nullptr;
}

UnitParent *GameBase::spawnSprinkler() {
	if (baseUnits[0]->units[1] == nullptr) {
		if (units->createUnit(UNIT_L_SPRINKLER, Vector2D(location.x - 1, location.y - 1), this)) {
			baseUnits[0]->units[1] = units->units.back();
			unitsCount++;

			return baseUnits[0]->units[1];
		}
	}
	return nullptr;
}

void GameBase::updateAtributes() {
	for (auto &units : baseUnits) {
		units->update();
	}
}

void GameBase::removeUnit(UnitParent *unit) {
	for (auto &composite : baseUnits) {
		for (int i = 0; i < composite->units.size(); i++) {
			if (composite->units[i] == unit) {
				composite->units[i] = nullptr;
				return;
			}
		}
	}
}

GameBase &GameBase::operator=(const GameBase &base) {
	if (&base == this) {
		return *this;
	}

	this->unitsCount = base.unitsCount;
	this->dew = base.dew;
	this->isActive = base.isActive;
	this->ligth = base.ligth;
	this->location = base.location;
	this->type = base.type;
	this->unitType01 = base.unitType01;
	this->unitType02 = base.unitType02;
	this->unitType03 = base.unitType03;

	for (int i = 0; i < 2; i++) {
		*this->baseUnits[i] = *base.baseUnits[i];
	}

	return *this;
}

UnitParent *GameBase::spawnUnit(char type) {
	if (units->createUnit(type, Vector2D(location.x - 1, location.y - 1), this)) {
		unitsCount++;
		return units->units.back();
	}

	return nullptr;
}
