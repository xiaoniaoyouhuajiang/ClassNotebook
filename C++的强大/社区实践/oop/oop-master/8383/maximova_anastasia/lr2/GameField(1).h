#pragma once
#include "Object.h"
#include "Unit.h"
#include "AbstractFactory.h"
#include "Cell.h"
#include <ctime>
#include <Windows.h>

class GameField {
protected:
	int width, height;
	int step;
	int maxUnits;
	Cell** field;	//двумерный массив клеток

public:
	GameField();
	GameField(int height, int width);

	GameField(const GameField& other);		//конструктор копирования
	GameField& operator = (const GameField& other);

	GameField(GameField&& other);			//конструктор переноса
	GameField& operator = (GameField&& other);

	void createField();
	void addBases();
	void coveredLands();

	void addPeople();
	void addNeutralObject();
	int addUnit(Unit* unit, int x, int y);

	void swapUnits(Cell& a, Cell& b);
	int checkSteps(int steps, int x, int y);
	int  movingUnit(int x, int y, int x2, int y2, int steps);

	int deleteUnit(int x, int y);
	int deleteNeutralObject(int x, int y);
	int deleteBase(int x, int y);

	Unit* getUnit(int x, int y);
	Landscape* getLandscape(int x, int y);
	NeutralObject* getNeutralObject(int x, int y);
	Base* getBase(char type);
	Base* getBase(int x, int y);

	int getHeight();
	int getWidth();
	int getStep();
	int getMaxUnits();

	~GameField();

};
