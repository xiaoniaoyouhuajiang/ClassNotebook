#pragma once
#include <vector>
#include "GameBoard.h"
#include "IUnit.h"

class Base:public IUnit{
private:
	double opposition;
	int maxBuildings;
	int numOfBuildings;
	std::vector <IUnit*> buildings;
public:
	Builds typeOfBuild() override;
	Base(int w, int h);
	std::vector <IUnit*> getBuildings();
	bool addBuild(int x, int y, Builds type, Board* board);
};