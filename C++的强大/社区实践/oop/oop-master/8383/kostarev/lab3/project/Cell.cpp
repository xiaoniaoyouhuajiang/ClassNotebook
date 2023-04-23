#include <iostream>
#include "Cell.h"
#include "Naming.h"
#include "Buildings.h"
#include "Base.h"
#include "Statistics.h"

Cell::Cell() {
	auto creatorL = new FabricOfLandscape();
	auto creatorN = new FabricOfNeutral();
	buildingOnCell = nullptr;
	switch (rand() % 20){
	case 0:
		neutralObject = creatorN->creatorNeutralObject(CHERNOZEM);
		break;
	case 1:
		neutralObject = creatorN->creatorNeutralObject(RELICS);
		break;
	case 2:
		neutralObject = creatorN->creatorNeutralObject(RADIATION);
		break;
	case 3:
		neutralObject = creatorN->creatorNeutralObject(GAS);
		break;
	default:
		neutralObject = nullptr;
		break;
	}
	landscape = creatorL->creatorLandsacpe(static_cast<Landscapes>(rand() % 3));
}

Cell::Cell(const Cell& oldCell) {
	this->buildingOnCell = oldCell.buildingOnCell;
	this->landscape = oldCell.landscape;
}

void Cell::addBuild(IUnit* build) {
	if (buildingOnCell == nullptr) {
		buildingOnCell = build;
	}
}

void Cell::addCityHall(int w, int h) {
	if (buildingOnCell == nullptr)
		buildingOnCell = new Base(w, h);
}

void Cell::removeBuild() {
	buildingOnCell = nullptr;
}

void Cell::aboutCell() {
	if (buildingOnCell != nullptr) {
		Builds typeOfBOnCell = (buildingOnCell)->typeOfBuild();
		if (typeOfBOnCell == CITY_HALL) {
			std::cout << "CITY HALL." << std::endl;
			auto stats = new Statistics(dynamic_cast<Base*>(buildingOnCell));
			std::cout << "Sum Saldo: " << stats->getSumSaldo() << std::endl;
			std::cout << "Sum Employment: " << stats->getSumEmployment() << std::endl;
			std::cout << "Sum Education: " << stats->getSumEducation() << std::endl;
			std::cout << "Sum Energy: " << stats->getSumEnergy() << std::endl;
			std::cout << "Sum Water: " << stats->getSumWater() << std::endl;
			std::cout << "Sum Satiety: " << stats->getSumSatiety() << std::endl;
			return;
		}
		std::cout << "Saldo: " << dynamic_cast<Building*>(buildingOnCell)->getSaldo() << std::endl;
		std::cout << "Energy: " << dynamic_cast<Building*>(buildingOnCell)->getEnergy() << std::endl;
		std::cout << "Water: " << dynamic_cast<Building*>(buildingOnCell)->getWater() << std::endl;
		std::cout << "Eat: " << dynamic_cast<Building*>(buildingOnCell)->getEat() << std::endl;
		if (typeOfBOnCell == DACHA || typeOfBOnCell == HRUSHCHOVKA) {
			std::cout << "Workmans: " << dynamic_cast<Apartment*>(buildingOnCell)->getWorkmans() << std::endl;
			std::cout << "Students: " << dynamic_cast<Apartment*>(buildingOnCell)->getStudents() << std::endl;
			std::cout << "Kids: " << dynamic_cast<Apartment*>(buildingOnCell)->getKids() << std::endl;
		}
		else if (typeOfBOnCell == FERMA || typeOfBOnCell == OFFICE) {
			std::cout << "Workmans: " << dynamic_cast<Production*>(buildingOnCell)->getVacancy() << std::endl;
		}
	}
	else {
		std::cout << "No build" << std::endl;
	}
}

bool Cell::isCityHall(){
	return (typeBuild() == 'C');
}

IUnit* Cell::getBuildOnCell(){
	return buildingOnCell;
}

ILandscape* Cell::getLandscape(){
	return landscape;
}

INeutral* Cell::getNeutral(){
	return neutralObject;
}

char Cell::typeBuild() {
	if (buildingOnCell != nullptr) {
		switch (buildingOnCell->typeOfBuild()) {
		case DACHA:
			return 'D';
		case HRUSHCHOVKA:
			return 'H';
		case FERMA:
			return 'F';
		case OFFICE:
			return 'O';
		case SCHOOL:
			return 'S';
		case VODOKANAL:
			return 'V';
		case POWERHOUSE:
			return 'P';
		case CITY_HALL:
			return 'C';
		}
	}
	else {
		switch (landscape->typeOfLandscape()){
		case HILL:
			return '^';
		case PLAIN:
			return '_';
		case LAKE:
			return '~';
		}
	}
}

int Cell::aboutCell_Saldo() {
	return dynamic_cast<Building*>(buildingOnCell)->getSaldo();
}