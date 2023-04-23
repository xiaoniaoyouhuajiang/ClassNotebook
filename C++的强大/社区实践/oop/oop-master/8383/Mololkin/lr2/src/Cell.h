#pragma once
#include <cstddef>
#include <ctime>
#include "IUnit.h"
#include "Shooters.h"
#include "Landscapes.h"
#include "Infantary.h"
#include "Mechanisms.h"
#include "Base.h"

class Cell
{
private:
	bool emptyOfCell;
	bool isUnitOnCell;
	IUnit* unitOnCell;
	Base* baseOnCell;
	LandscapeProxy* cellLandscape;

public:
	Cell();
	~Cell();
	Cell(Cell& other);
	bool getEmptyOfCell();
	bool getIsUnitOnCell();
	IUnit * getUnitOnCell();
	Base* getBaseOnCell();
	void setUnitOnCell(IUnit * unitOnCell);
	void setBaseOnCell(Base* baseOnCell);
	Landscapes getCellLandscape();
	IUnit* killUnitOnCell();
	void delBaseOnCell();
	std::string getCell();
};

