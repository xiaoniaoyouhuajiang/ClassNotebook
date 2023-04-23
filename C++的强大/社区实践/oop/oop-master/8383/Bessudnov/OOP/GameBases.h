#pragma once
#include "GameUnits.h"
#include <vector>
#include <iostream>
#include <algorithm>

class Vector2D;
class GameField;
class UnitParent;

enum GameBaseTypes {Zero, One, Two, Three, Four};

class GameBaseAtribute {
private:
	int val;
public:
	GameBaseAtribute() {
		val = 0;
	}

	void setVal(int val) {
		this->val = val;
	}

	int getVal() {
		return this->val;
	}

	void increaseVal(int increment) {
		val += increment;
	}

	GameBaseAtribute &operator=(const GameBaseAtribute &atribute) {
		if (&atribute == this) {
			return *this;
		}

		val = atribute.val;

		return *this;
	}

	friend std::ostream &operator<<(std::ostream &os, const GameBaseAtribute &atribute) {
		os << atribute.val;
		return os;
	}

	friend std::istream &operator>>(std::istream &is, GameBaseAtribute &atribute) {
		is >> atribute.val;
		return is;
	}
};


class GameBase {
protected:
	GameUnits *units;
public:
	int unitsCount;
	GameBaseAtribute dew;
	GameBaseAtribute ligth;
	bool isActive = false;
	GameBaseTypes type;
	Vector2D location;
	std::vector<CompositeUnit*> baseUnits;
	char unitType01;
	char unitType02;
	char unitType03;

	~GameBase() = default;
	GameBase();
	GameBase(GameUnits *units);
	GameBase(const GameBase *gameBase, GameUnits *gameUnits);

	virtual UnitParent *spawnU1();
	virtual UnitParent *spawnU2();
	virtual UnitParent *spawnU3();
	UnitParent *spawnCollector();
	UnitParent *spawnSprinkler();
	void updateAtributes();
	void removeUnit(UnitParent *unit);

	GameBase &operator=(const GameBase &base);

	UnitParent *spawnUnit(char type);
};

class DefaultBase : public GameBase {
public:
	DefaultBase(GameUnits *units) : GameBase::GameBase(units) {
		type = GameBaseTypes::Zero;
		baseUnits[1]->setSize(1);
	}
	UnitParent *spawnU1() {
		std::cout << "Not Rigth Now";
		return nullptr;
	};
	UnitParent *spawnU2() {
		std::cout << "Not Rigth Now";
		return nullptr;
	};
	UnitParent *spawnU3() {
		std::cout << "Not Rigth Now";
		return nullptr;
	};
};

class OneBase : public GameBase {
public:
	OneBase(GameUnits *units) : GameBase::GameBase(units) {
		type = GameBaseTypes::One;
		unitType01 = UNIT_D_FLY;
		unitType02 = UNIT_L_BEE;
		unitType03 = UNIT_D_COAL;
	}
};

class TwoBase : public GameBase {
public:
	TwoBase(GameUnits *units) : GameBase::GameBase(units) {
		type = GameBaseTypes::Two;
		unitType01 = UNIT_D_COAL;
		unitType02 = UNIT_L_FLOWER;
		unitType03 = UNIT_L_BEE;
	}
};

class ThreeBase : public GameBase {
public:
	ThreeBase(GameUnits *units) : GameBase::GameBase(units) {
		type = GameBaseTypes::Three;
		unitType01 = UNIT_L_FLOWER;
		unitType02 = UNIT_D_FLY;
		unitType03 = UNIT_D_COAL;
	}
};

class FourBase : public GameBase {
public:
	FourBase(GameUnits *units) : GameBase::GameBase(units) {
		type = GameBaseTypes::Four;
		unitType01 = UNIT_D_FLY;
		unitType02 = UNIT_L_FLOWER;
		unitType03 = UNIT_D_COAL;
	}
};


class GameBasesContainer {
private:
	GameField *field;
public:
	std::vector<GameBase*> bases;
	int currentBaseIndex;

	void setBaseType(GameBaseTypes baseType, int index, GameUnits *gameUnits);
	void switchBase(bool forward);
	UnitParent *spawnUnit(int type);

	void spawnDefaultBase(GameUnits *units, float position);
	GameBase* getBaseAtLocation(Vector2D loc);
	GameBasesContainer() = default;
	GameBasesContainer(GameField *field);
	GameBasesContainer(GameField &field, GameUnits &units);
	~GameBasesContainer();

	GameBasesContainer &operator=(const GameBasesContainer &gameBasesContainer);
};

