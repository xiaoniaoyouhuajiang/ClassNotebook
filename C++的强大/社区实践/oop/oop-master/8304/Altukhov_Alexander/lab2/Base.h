#pragma once
#include <vector>
//#include "Unit.h"
#include "Field.h"


enum class UnitTypes;

class Field;
class Unit;

class Base {

	int hp;

	int x;
	int y;

	std::vector<Unit*> units;
	int unitsCounter;
	Field* parentField;

public:
	Base();
	~Base();
	
	Field* getParentField();
	void setParentField(Field*& field);

	void setBase(int x, int y);

	int getX();
	int getY();

	void setHp(int val);
	Unit*& getUnit(int id);
	int getHp();

	Unit* createAndSetUnit(UnitTypes type, int lvl, int x, int y);
	void deleteUnit(Unit*& unit);
};

