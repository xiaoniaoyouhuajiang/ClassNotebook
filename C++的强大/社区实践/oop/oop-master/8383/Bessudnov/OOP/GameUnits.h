#pragma once
#include "UnitParent.h"
#include <vector>
#include <algorithm>

#define UNITS_MAX 7

class Vector2D;
class GameField;
class GameUnits;
class GameBasesContainer;
class GameBase;


class UnitsFactory {
public:
	virtual FlyingUnits *createFlyingUnit(GameField *field, GameUnits *units, GameBase *base) = 0;
	virtual GroundUnits *createGroundUnit(GameField *field, GameUnits *units, GameBase *base) = 0;
	virtual SmallUnits *createSmallUnit(GameField *field, GameUnits *units, GameBase *base) = 0;
	~UnitsFactory() {}
};

class UnitsFactoryLigth : public UnitsFactory {
public:
	FlyingUnits *createFlyingUnit(GameField *field, GameUnits *units, GameBase *base) {
		return new BeeUnit(field, units, base);
	}

	GroundUnits *createGroundUnit(GameField *field, GameUnits *units, GameBase *base) {
		return new FlowerUnit(field, units, base);
	}

	SmallUnits *createSmallUnit(GameField *field, GameUnits *units, GameBase *base) {
		return new SprinklerUnit(field, units, base);
	}
};

class UnitsFactoryDew : public UnitsFactory {
public:
	FlyingUnits *createFlyingUnit(GameField *field, GameUnits *units, GameBase *base) {
		return new FlyUnit(field, units, base);
	}

	GroundUnits *createGroundUnit(GameField *field, GameUnits *units, GameBase *base) {
		return new CoalUnit(field, units, base);
	}

	SmallUnits *createSmallUnit(GameField *field, GameUnits *units, GameBase *base) {
		return new CollectorUnit(field, units, base);
	}

};

class GameUnits {
public:
	std::vector<UnitParent*> units;
	int currentUnitIndex;
	Vector2D borders;

	UnitsFactoryLigth unitsFactoryLigth;
	UnitsFactoryDew unitsFactoryDew;

	void updateBorders(Vector2D fieldBorders);
	void switchUnit(bool forward);
	bool createUnit(char type, Vector2D location, GameBase *base);
	bool moveUnit(Vector2D direction);

	UnitParent *getUnit(Vector2D location);
	void ereaseUnit(UnitParent *unit);

	GameUnits() = default;
	GameUnits(std::string unitsFileName, Vector2D fieldBorders);
	GameUnits(Vector2D fieldBorders, GameField *field, GameBasesContainer *bases);
	~GameUnits();

	void loadGameUnits(const GameUnits *gameUnits) {
		units.clear();
		units.resize(gameUnits->units.size());
		std::copy(gameUnits->units.begin(), gameUnits->units.end(), units.begin());
		//borders = gameUnits->borders;
		currentUnitIndex = gameUnits->currentUnitIndex;
	}

	GameUnits &operator=(const GameUnits &units) {
		if (&units == this) {
			return *this;
		}

		std::copy(units.units.begin(), units.units.end(), this->units.end());
		this->currentUnitIndex = units.currentUnitIndex;
		this->borders = units.borders;

		return *this;
	}

private:
	int overlapCheck(Vector2D targetLocation);
	GameField *field;
	GameBasesContainer *bases;
};

