#pragma once
#include "Tile.h"
#include "Base.h"
constexpr auto DEFAULT_W = 8;
constexpr auto DEFAULT_H = 8;
constexpr auto MAX_OBJECTS_AMOUNT = 50;

//enum class UnitTypes {
//	MELEE, RANGE, HORSEMAN
//};
struct Tile;
class Unit;
class Base;
class Field {

	Tile** fieldArr;
	int width;
	int height;
	int amountOfObjects;

public:

	Field();
	Field(int w, int h);
	Field(const Field& field);
	~Field();
	void totalCopy(Field*& fToCopy, Field*& fToPaste);//последний аргумент это то же самое что this только не константный
	int getW();
	int getH();
	Tile& getTile(int x, int y);

	int getAmountOfObjects() { return amountOfObjects; }
	void raiseAmountOfObjects() { amountOfObjects++; }
	void lowAmountOfObjects() { amountOfObjects--; }
	void visualizeField();
	//Unit* createAndSetUnit(UnitTypes type, int lvl, int x, int y, Field*& f);
	Base* createAndSetBase(Field*& f);
	//NeutralObject* createAndSetNeutralObject(NeutralObjectTypes type, int);
	//void deleteUnit(Unit*& unit);
	void deleteBase(Base*& base);
};

