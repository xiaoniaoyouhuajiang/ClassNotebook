#pragma once
#include "Naming.h"
#include "IUnit.h"
#include "ILandscape.h"
#include "INeutral.h"

class Cell {
private:
	IUnit* buildingOnCell;
	ILandscape* landscape;
	INeutral* neutralObject;
public:
	Cell();
	Cell(const Cell& oldCell);
	void addBuild(IUnit* build);
	void addCityHall(int w, int h);
	void aboutCell();
	bool isCityHall();
	IUnit* getBuildOnCell();
	ILandscape* getLandscape();
	INeutral* getNeutral();
	int aboutCell_Saldo();
	void removeBuild();
	char typeBuild();
};