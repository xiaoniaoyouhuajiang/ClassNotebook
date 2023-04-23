#pragma once
#include "Field.h"
#include "IUnit.h"
class Field;
enum class UnitTypes;
class Unit: public IUnit {

	int x;
	int y;
	Field*  parentField;

	int attack;
	int hp;
	int armor;
	int haste;
	int range;
	int level;
	int cost;
	UnitTypes type;

public:

	Unit() :x(-1), y(-1), parentField(nullptr) {};
	~Unit();

	int getAttack();
	int getHp();
	int getArmor();
	int getHaste();
	int getRange();
	int getLevel();
	int getCost();
	UnitTypes getUnitType();

	Field* getParentField();
	int getX();
	int getY();

	void setAttack(int val);
	void setHp(int val);
	void setArmor(int val);
	void setHaste(int val);
	void setRange(int val);
	void setLevel(int val);
	void setCost(int val);
	void setUnitType(UnitTypes val);

	void setParentField(Field *& field);


	virtual void doAttack();
	virtual void doMove(int x, int y);
};

