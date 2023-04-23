#include "GameField.h" //check
//#include "FieldBlock.h"
#include "Units.h"
#include "Base.h"
#include "Factory.h"
#include "FieldBlock.h"
#include <string>

Base::Base(int size) {
	this->size = size;
    x = 5;
	y = 0;
    health = 99;
    maxUnits = 12;
	numOfUnits = 0;
}

Base::Base() {
    this->size = 0;
    x = 0;
    y = 0;
    health = 0;
    maxUnits = 0;
    numOfUnits = 0;
}


void Base::setBase(std::vector<int> param) {
	this->x = param[0];
	this->y = param[1];
	this->health = param[2];
	this->maxUnits = param[3];
	this->numOfUnits = param[4];
}


Base::~Base() {
	
}

Unit* Base::createArcher(int x, int y) {
	if (numOfUnits <= maxUnits) {
		numOfUnits++;
		ArcherFactory archerFact;
		return archerFact.createUnit(x, y);
	}
	return NULL;
}

Unit* Base::createBallista(int x, int y) {
	if (numOfUnits <= maxUnits) {
		numOfUnits++;
		BallistaFactory ballistaFact;
		return ballistaFact.createUnit(x, y);
	}
	return NULL;
}

Unit* Base::createAtFarm(int x, int y) {
	if (numOfUnits <= maxUnits) {
		numOfUnits++;
		AtFarmFactory atFarmFact;
		return atFarmFact.createUnit(x, y);
	}
	return NULL;
}

Unit* Base::createBomber(int x, int y) {
	if (numOfUnits <= maxUnits) {
		numOfUnits++;
		BomberFactory bombFact;
		return bombFact.createUnit(x, y);
	}
	return NULL;
}

Unit* Base::createGeneral(int x, int y) {
	if (numOfUnits <= maxUnits) {
		numOfUnits++;
		GeneralBombFactory generalFact;
		return generalFact.createUnit(x, y);
	}
	return NULL;
}


void Base::deleteUnit(int x, int y, GameField& board) { //rework
	numOfUnits--;
	board.field[y * board.size + x].unit = nullptr;
	board.numOfEmptyBlocks++;
}

void Base::enableSpots() {
	std::cout << "There are " << maxUnits - numOfUnits << " spots on the board\n";
}

void Base::baseHealth() {
	std::cout << "Base hp is " << health << "\n";
}

std::ostream& operator<<(std::ostream& out, const Base& base) {
	out << "Base with x = " + std::to_string(base.x) + " y = " + std::to_string(base.y) + " have " + std::to_string(base.health) + " health.\n";
	return out;
}

/*
DefBase::DefBase(int side){
    size = side;
    x = 9;
    y = 14;
    health = 15;
    maxUnits = 15;
    numOfUnits = 0;
}
*/
DefBase::DefBase(int side){
    this->x = 9;
    this->y = 14;
    this->size = side;
    this->health = 10;
    this->maxUnits = 15;
    this->numOfUnits = 0;
    this->useless = 0;
}




