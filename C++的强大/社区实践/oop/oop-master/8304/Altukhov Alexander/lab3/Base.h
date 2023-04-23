#pragma once
#include <vector>
#include <map>
//#include "Unit.h"
#include "Field.h"


enum class UnitTypes;

class Field;
class Unit;

class Base {

	int hp;

	int x;
	int y;

	//std::vector<Unit*> units;
	std::map<int, Unit*> units;
	int lastId;
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
	Unit* getUnit(int id);
	int getHp();

	void writeBaseState();
	bool writeUnitInfo(int id);//true если успешно

	Unit* createAndSetUnit(UnitTypes type, int lvl, int x=0, int y=0);
	void deleteUnit(Unit*& unit);
	std::map<int, Unit*>::iterator deleteUnit(std::map<int, Unit*>::iterator it);
};

