#include "GameField.h"
#include "FieldBlock.h"
#include "Landscape.h"
#include <iostream>
#include <iomanip>

//#include "Neutral.h"


GameField::GameField(int side) {
	Plain* mainPlain = new Plain;
	Mountain* mainMountain = new Mountain;
	Lake* mainLake = new Lake;
	if (side < 2) {
		side = 2;
	}
	if (side > 8) {
		side = 8;
	}
	this->size = side;
	this->numOfEmptyBlocks = size*size;
	this->field = new FieldBlock[side * side];
	for (int i = 0; i < side; i++) { // i equal y
		for (int j = 0; j < side; j++) { //j equal x
			field[i * side + j].x = j;
			field[i * side + j].y = i;
			field[i * side + j].landType = mainPlain;
			if ((i * side + j) == 14 || (i * side + j) == 25) {
				field[i * side + j].landType = mainMountain; //mount
				field[i * side + j].isEmpty = false;
			}
			if ((i * side + j) == 29) {
				field[i * side + j].landType = mainLake; //lakers
				field[i * side + j].isEmpty = false;
			}
		}
	}
}


GameField::~GameField() {
	delete []field;
}


GameField::GameField() {
	this->size = 0;
	while((size < 2)||(size > 8)){
		std::cout << "type N:\n";
		std::cin >> this->size;
	}
	this->numOfEmptyBlocks = 0;
	this->field = new FieldBlock[size * size];
	for (int i = 0; i < size; i++) { // i equal y
		for (int j = 0; j < size; j++) { //j equal x
			field[i * size + j].x = j;
			field[i * size + j].y = i;
		}
	}
}


void GameField::draw() {
	for (int i = 0; i < size; i++) {
		for (int k = 0; k < size; k++) {
			std::cout << " -------";
		}
		std::cout << "\n";
		for (int j = 0; j < size; j++) {

			std::cout << "|" << std::setw(4);
		
			if (field[i * size + j].landType->getType() == 2) {
				std::cout << "~" <<  std::setw(3) << "|";
				continue;
			}
			if (field[i * size + j].landType->getType() == 1) {
				std::cout << "^" << std::setw(3) << "|";
				continue;
			}
			//else {
				std::cout << field[i * size + j].unitType <<  std::setw(3) << "|";
		//	}
		}
		std::cout << std::endl;
	}
	for (int k = 0; k < size; k++) {
		std::cout << " -------";
	}
}


GameField::GameField(const GameField& board) {
	this->numOfEmptyBlocks = board.numOfEmptyBlocks;
	this->size = board.size;
	field = new FieldBlock[size * size];
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			field[i * size + j].x = j;
			field[i * size + j].y = i;
			field[i * size + j].isEmpty = board.field[i * size + j].isEmpty;
			field[i * size + j].unitIndex = board.field[i * size + j].unitIndex;
			field[i * size + j].unitType = board.field[i * size + j].unitType;
		}
	}
}

void GameField::putUnitOn(int x, int y, int type, int index, GameField& board) {
	board.field[y * board.size + x].unitType = type;
	board.numOfEmptyBlocks--;
	board.field[y * board.size + x].isEmpty = false;
	board.field[y * board.size + x].unitIndex = index;
}


Proxy::Proxy(GameField* ptr) {
	this->gameField = ptr;
}

bool Proxy::proxyChecker(int x, int y) {
	if (gameField->field[x + gameField->size * y].landType->getType() == 0 && gameField->field[x + gameField->size * y].unit == NULL) {
		return true;
	}
	return false;
}

bool Proxy::proxyIsUnit(int x, int y) {
	if (gameField->field[x + gameField->size * y].unit == NULL) {
		return false;
	}
	return true;
}
