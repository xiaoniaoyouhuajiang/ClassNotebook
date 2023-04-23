#include "Base.h"
#include "Buildings.h"
#include "Statistics.h"

Builds Base::typeOfBuild(){
	return CITY_HALL;
}

Base::Base(int w, int h){
	opposition = 0.0;
	maxBuildings = w*h/4;
	numOfBuildings = 0;
}

std::vector<IUnit*> Base::getBuildings(){
	return buildings;
}

bool Base::addBuild(int x, int y, Builds type, Board* board){
	if (numOfBuildings < maxBuildings) {
		auto creator = new FactoryOfBuildings();
		auto build = creator->creator(type);
		if (board->setBuild(x, y, build)) {
			buildings.push_back(build);
			numOfBuildings++;
			return true;
		};
		return false;
	}
	return false;
}
