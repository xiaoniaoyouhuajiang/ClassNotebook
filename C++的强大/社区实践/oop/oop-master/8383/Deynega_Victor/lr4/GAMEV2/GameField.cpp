#include "GameField.h" //check
#include "FieldBlock.h"
#include "Landscape.h"
#include <iostream>
#include <iomanip>



GameField::GameField(int side) {
	bx = 0;
	by = 0;
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
			}
			if ((i * side + j) == 29) {
				field[i * side + j].landType = mainLake; //lakers
			}
		}
	}
}


GameField::~GameField() {
	delete []field;
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
				std::cout << "~" << std::setw(3) << "|";
				continue;
			}
			if (field[i * size + j].landType->getType() == 1) {
				std::cout << "^" << std::setw(3) << "|";
				continue;
			}
			if (i == by && j == bx) {
				std::cout << "B" << std::setw(3) << "|";
				continue;
			}
			
			std::cout << field[i * size + j].getUnitType() << std::setw(3) << "|";

		}
		std::cout << std::endl;
	}
	for (int k = 0; k < size; k++) {
		std::cout << " -------";
	}
}


GameField::GameField(const GameField& board) {
	bx = 3;
	by = 0;
	this->numOfEmptyBlocks = board.numOfEmptyBlocks;
	this->size = board.size;
	field = new FieldBlock[size * size];
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			field[i * size + j].x = j;
			field[i * size + j].y = i;
		}
	}
}



Proxy::Proxy(GameField* ptr) {
	this->gameField = ptr;
}

bool Proxy::proxyChecker(int x, int y) {
	if (gameField->field[x + gameField->size * y].landType->getType() == 0 && gameField->field[x + gameField->size * y].unit == NULL && (gameField->bx != x || gameField->by != y)) {
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


bool Proxy::proxyIsLansdscape(int x, int y) {
	if (gameField->field[x + gameField->size * y].landType->getType() == 2 || gameField->field[x + gameField->size * y].landType->getType() == 1) {
		return 1;
	}
	return 0;
}
