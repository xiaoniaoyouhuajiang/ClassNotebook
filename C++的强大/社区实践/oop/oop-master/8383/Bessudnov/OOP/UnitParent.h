#pragma once
#include "GameUtilities.h"
#include "Interfaces.h"
#include <vector>
#include <iostream>
#include <algorithm>
class NeutralObject;
class GameField;
class GameUnits;
class GameBase;

class UnitAtribute {
public:
	int parameterValueAbsolute;
	int parameterValueCurrent;

	void setPar(int value) {
		parameterValueAbsolute = value;
		parameterValueCurrent = value;
	}

	void increasePar(int increment) {
		parameterValueCurrent += increment;
	}


	UnitAtribute() : parameterValueAbsolute(0), parameterValueCurrent(0) {};
	UnitAtribute(int val) : parameterValueAbsolute(val), parameterValueCurrent(val) {};

	UnitAtribute &operator=(const UnitAtribute &atribute) {
		if (&atribute == this) return *this;

		this->parameterValueAbsolute = atribute.parameterValueAbsolute;
		this->parameterValueCurrent = atribute.parameterValueCurrent;

		return *this;

	}

	friend std::ostream &operator<<(std::ostream &os, const UnitAtribute &atribute) {
		os << atribute.parameterValueCurrent << " " << atribute.parameterValueAbsolute;
		return os;
	}

	friend std::istream &operator>>(std::istream &is, UnitAtribute &atribute) {
		is >> atribute.parameterValueCurrent;
		is >> atribute.parameterValueAbsolute;
		return is;
	}
};

typedef struct UnitProperties {
	bool isActive;
	char type;
	Vector2D location;
	UnitAtribute dew;
	UnitAtribute ligth;
	UnitAtribute moves;
	UnitAtribute damage;
	UnitAtribute sugar;

	UnitProperties() : isActive(false), type('1'), location(Vector2D(0, 0)), dew(), 
		ligth(), moves(), damage(), sugar() {	
	}

	UnitProperties &operator=(const UnitProperties &props) {
		if (this == &props) return *this;

		isActive = props.isActive;
		type = props.type;
		location = props.location;
		dew = props.dew;
		ligth = props.ligth;
		moves = props.moves;
		damage = props.damage;
		sugar = props.sugar;

		return *this;
	}

	friend std::ostream &operator<<(std::ostream &os, const UnitProperties &props) {
		os << props.isActive << " ";
		os << props.type << " ";
		os << props.location << " ";
		os << props.dew << " ";
		os << props.ligth << " ";
		os << props.moves << " ";
		os << props.damage << " ";
		os << props.sugar << " ";
		return os;
	}

	friend std::istream &operator>>(std::istream &is, UnitProperties &props) {
		is >> props.isActive;
		is >> props.type;
		is >> props.location;
		is >> props.dew;
		is >> props.ligth;
		is >> props.moves;
		is >> props.damage;
		is >> props.sugar;
		return is;
	}


}UnitProperties;


class UnitParent : public IUnits, public IObserver {
public:
	UnitProperties unitProps;

	UnitParent() = default;
	UnitParent(const UnitParent &unit);
	UnitParent &operator=(const UnitParent &unit);
	virtual ~UnitParent();

	void updateLocation(Vector2D newBorders);
	void move(Vector2D direction, Vector2D borders);
	virtual void attack(Vector2D direction) = 0;
	virtual void update() = 0;

	virtual void recieveDamage(int damage) = 0;
	virtual void sacrafice() = 0;
	friend void operator+(UnitParent &unit, NeutralObject *object);

protected:
	void setNewUnitLocation(Vector2D unitOffset, Vector2D borders);

};

class FlyingUnits : public UnitParent {
protected:
	GameField *gameField;
	GameUnits *units;
	GameBase *baseOwner;
public:
	FlyingUnits(GameField *gameField, GameUnits *units, GameBase *base) : gameField(gameField), units(units), baseOwner(base) {
	
	}

	void recieveDamage(int damage);
	void sacrafice();
};

class BeeUnit : public FlyingUnits {
public:

	BeeUnit(GameField *gameField, GameUnits *units, GameBase *base) : FlyingUnits(gameField, units, base) {
		unitProps.type = UNIT_L_BEE;
		unitProps.dew.setPar(3);
		unitProps.ligth.setPar(0);
		unitProps.moves.setPar(5);
		unitProps.damage.setPar(1);
		unitProps.sugar.setPar(2);
	}
	void update() {};
	void attack(Vector2D direction);
};

class FlyUnit : public FlyingUnits {
public:
	FlyUnit(GameField *gameField, GameUnits *units, GameBase *base) : FlyingUnits(gameField, units, base) {
		unitProps.type = UNIT_D_FLY;
		unitProps.dew.setPar(0);
		unitProps.ligth.setPar(3);
		unitProps.moves.setPar(4);
		unitProps.damage.setPar(2);
		unitProps.sugar.setPar(3);
	}
	void update() {};
	void attack(Vector2D direction);
};



class SmallUnits : public UnitParent {
protected:
	GameField *gameField;
	GameUnits *units;
	GameBase *baseOwner;
public:
	SmallUnits(GameField *gameField, GameUnits *units, GameBase *base) : gameField(gameField), units(units), baseOwner(base) {
		
	}
	void recieveDamage(int damage);
	void sacrafice();
};

class CollectorUnit : public SmallUnits {
public:
	CollectorUnit(GameField *field, GameUnits *units, GameBase *base) : SmallUnits(field, units, base) {
		unitProps.type = UNIT_D_COLLECTOR;
		unitProps.dew.setPar(1);
		unitProps.ligth.setPar(0);
		unitProps.moves.setPar(1);
		unitProps.damage.setPar(1);
		unitProps.sugar.setPar(1);
	}
	void update() {};
	void attack(Vector2D direction);
};

class SprinklerUnit : public SmallUnits {
public:
	SprinklerUnit(GameField *field, GameUnits *units, GameBase *base) : SmallUnits(field, units, base) {
		unitProps.type = UNIT_L_SPRINKLER;
		unitProps.dew.setPar(0);
		unitProps.ligth.setPar(1);
		unitProps.moves.setPar(1);
		unitProps.damage.setPar(1);
		unitProps.sugar.setPar(1);
	}
	void update() {};
	void attack(Vector2D direction);
};



class GroundUnits : public UnitParent {
protected:
	GameField *gameField;
	GameUnits *units;
	GameBase *baseOwner;
public:
	GroundUnits(GameField *gameField, GameUnits *units, GameBase *base) : gameField(gameField), units(units), baseOwner(base) {
	
	}
	void recieveDamage(int damage);
	void sacrafice();
};

class CoalUnit : public GroundUnits {
public:
	CoalUnit(GameField *field, GameUnits *units, GameBase *base) : GroundUnits(field, units, base) {
		unitProps.type = UNIT_D_COAL;
		unitProps.dew.setPar(4);
		unitProps.ligth.setPar(0);
		unitProps.moves.setPar(3);
		unitProps.damage.setPar(3);
		unitProps.sugar.setPar(4);
	}
	void update() {};
	void attack(Vector2D direction);
};

class FlowerUnit : public GroundUnits {
public:

	FlowerUnit(GameField *field, GameUnits *units, GameBase *base) : GroundUnits(field, units, base) {
		unitProps.type = UNIT_L_FLOWER;
		unitProps.dew.setPar(0);
		unitProps.ligth.setPar(5);
		unitProps.moves.setPar(4);
		unitProps.damage.setPar(2);
		unitProps.sugar.setPar(3);
	}
	void update() {};
	void attack(Vector2D direction);
};

class CompositeUnit : public UnitParent {
public:
	std::vector<UnitParent*> units;

	void addUnit(UnitParent* unit) {
		units.push_back(unit);
	}

	void setSize(size_t size) {
		units.resize(size);
	}

	~CompositeUnit() {
		units.clear();
	}

	void recieveDamage(int damage) {
		for (auto &unit : units) {
			unit->recieveDamage(damage);
		}
	}


	void update() {
		for (auto &unit : units) {
			unit->update();
		}
	}

	void attack(Vector2D direction) {
		for (auto &unit : units) {
			unit->attack(direction);
		}
	}

	int getUnitsCount() {
		int count = 0;
		for (auto &unit : units) {
			if (unit) {
				count++;
			}
		}

		return count;
	}

	CompositeUnit &operator=(const CompositeUnit &composite) {
		if (&composite == this) {
			return *this;
		}

		std::copy(composite.units.begin(), composite.units.end(), this->units.begin());

		return *this;
	}

	void sacrafice() {
		for (auto &unit : units) {
			unit->sacrafice();
		}
	}

	friend std::ostream &operator<<(std::ostream &os, const CompositeUnit composite) {
		for (int i = 0; i < composite.units.size(); i++) {
			if (composite.units[i]) {
				os << i << " " << composite.units[i]->unitProps << std::endl;
			}
		}
		return os;
	}

	friend std::istream &operator<<(std::istream &is, const CompositeUnit composite) {
		for (auto &unit : composite.units) {
			if (unit) {
				is >> unit->unitProps;
			}
		}
		return is;
	}
};

