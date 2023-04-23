#include "GameField.h" //check
#include "FieldBlock.h"
#include "Landscape.h"
#include <iostream>
#include <iomanip>
//#include<vector>


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


GameField::GameField() {
	int side = 20;
	bx = 0;
	by = 0;
	Plain* mainPlain = new Plain;
	Mountain* mainMountain = new Mountain;
	Lake* mainLake = new Lake;
	this->size = side;
	this->numOfEmptyBlocks = size * size;
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


Memento* GameField::createMemento(int health, int turn, int units) {//ne rabotaet ofc
	std::string message;
	message += "0_" + std::to_string(this->size) + "\n\t";
	for (int i = 0; i < this->size; i++) { // i equal y
		for (int j = 0; j < this->size; j++) { //j equal x
			message += std::to_string(field[i * this->size + j].landType->getType()); //land type
			message += std::to_string(field[i * this->size + j].getUnitType()); //unit type
			if ((i * j) == (this->size - 1) * (this->size - 1)) {
				if (field[i * this->size + j].neutralPtr != nullptr) {
					message += std::to_string(field[i * this->size + j].neutralPtr->effect()) + "\n"; //neutral 
				}
				else {
					message += "0\n";
				}
			}
			else {
				if (field[i * this->size + j].neutralPtr != nullptr) {
					message += std::to_string(field[i * this->size + j].neutralPtr->effect()) + "_"; //neutral 
				}
				else {
					message += "0_";
				}
			}
		}
	}
	message += "1_" + std::to_string(bx) + "_" + std::to_string(by) + "_" + std::to_string(health) + "_" + std::to_string(size * size / 2);
	message += "_" + std::to_string(units) + "\n";
	message += "2_" + std::to_string(turn) + "\n";
	return new Memento(message, false);
}


bool GameField::loadMemento(std::vector<int>& param) {
	std::string saveString;
	Memento save(saveString, true);
	if (save.saveString == "NULL") {
		std::cout << "Wrong name!\n";
		return false;
	}
	if (!save.isValid()) {
		std::cout << "Save damaged!\n";
		return false;
	}

	//delete this->field;
	int pos = 2;
	this->size = save.getNum(pos);
	pos += 2;
	this->field = new FieldBlock[this->size * this->size];
	for (int i = 0; i < this->size; i++) {
		for (int j = 0; j < this->size; j++) {
			std::vector<int> info;
			save.getNum(pos, info);
			field[i * this->size + j].setNeutral(info[2]);
			field[i * this->size + j].setUnit(info[1]);
			field[i * this->size + j].setLand(info[0]);
			info.clear();
		}
	}
	pos+=2;
	for (int i = 0; i < 5; i++) {
		param.push_back(save.getNum(pos));
		pos++;
	}
	
	return true;
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
