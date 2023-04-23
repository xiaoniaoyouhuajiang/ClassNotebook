#include "Field.h"
#include "Tile.h"
#include <iostream>
#include "MainUnitFactory.h"
#include "MeleeFactory.h"
#include "RangeFactory.h"
#include "HorsemanFactory.h"

Field::Field() : width(DEFAULT_W), height(DEFAULT_H), amountOfObjects(0) {

	fieldArr = new Tile * [width];
	for (int i = 0; i < width; i++) {
		fieldArr[i] = new Tile[height];
	}
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			fieldArr[i][j] = { i, j };
		}
	}
}

Field::Field(int w, int h) : width(w), height(h), amountOfObjects(0) {

	fieldArr = new Tile * [width];
	for (int i = 0; i < width; i++) {
		fieldArr[i] = new Tile[height];
	}
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			fieldArr[i][j] = { i, j };
		}
	}
}

Field::Field(const Field& field) {//копирование без юнитов, они удаляются


	Tile** anotherFieldArr = new Tile * [field.width];
	for (int i = 0; i < field.width; i++) {
		anotherFieldArr[i] = new Tile[field.height];
	}
	for (int i = 0; i < field.width; i++) {
		for (int j = 0; j < field.height; j++) {
			anotherFieldArr[i][j] = { i, j};
		}
	}

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			if (this->getTile(i, j).isOccupied) {
				this->deleteUnit(this->getTile(i, j).occupiedBy);
			}
		}

		delete[] fieldArr[i];
	}
	delete[] fieldArr;

	width = field.width;
	height = field.height;
	amountOfObjects = 0;
	fieldArr = anotherFieldArr;

}

void Field::totalCopy(Field*& fToCopy, Field*& fToPaste) {//this==fToPaste

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			if (this->getTile(i, j).isOccupied) {
				this->deleteUnit(this->getTile(i, j).occupiedBy);
			}
		}

		delete[] fieldArr[i];
	}
	delete[] fieldArr;


	fieldArr = new Tile * [fToCopy->width];
	for (int i = 0; i < fToCopy->width; i++) {
		fieldArr[i] = new Tile[fToCopy->height];
	}
	for (int i = 0; i < fToCopy->width; i++) {
		for (int j = 0; j < fToCopy->height; j++) {
			fieldArr[i][j] = { i, j };
			if (fToCopy->getTile(i, j).isOccupied) {
				this->createAndSetUnit(fToCopy->getTile(i, j).occupiedBy->getUnitType(), fToCopy->getTile(i, j).occupiedBy->getLevel(), i, j, fToPaste);
			}
		}
	}

	width = fToCopy->width;
	height = fToCopy->height;
	amountOfObjects = fToCopy->amountOfObjects;
}


Field::~Field() {
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			if (this->getTile(i, j).isOccupied) {
				this->deleteUnit(this->getTile(i, j).occupiedBy);
			}
		}

		delete[] fieldArr[i];
	}
	delete[] fieldArr;
}

int Field::getW() {
	return width;
}

int Field::getH() {
	return height;
}

Tile& Field::getTile(int x, int y) {
	//надо обработать выход за пределы
	return fieldArr[x][y];
}

void Field::visualizeField() {

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
		
			std::cout << " " << (this->getTile(i, j).isOccupied ? "1" : "0");
		}
		std::cout << "\n";
	}
	std::cout << "\n\n";
}

Unit* Field::createAndSetUnit(UnitTypes type, int lvl, int x, int y, Field*& f) {

	if (MAX_OBJECTS_AMOUNT == amountOfObjects) {
		std::cout << "Поле переполнено!\n";
		return nullptr;
	}
	if (this->getTile(x, y).isOccupied) {
		std::cout << "Клетка занята!\n";
		return nullptr;
	}
	if ((x >= width) || (y >= height)) {
		std::cout << "Выход за пределы поля!\n";
	}

	MainUnitFactory* factory;
	Unit* unit;
	if (type == UnitTypes::MELEE) {
		factory = new MeleeFactory;
	}
	else if (type == UnitTypes::RANGE) {
		factory = new RangeFactory;
	}
	else {//if (type == UnitTypes::HORSEMAN) {
		factory = new HorsemanFactory;
	}
	if (lvl == 1) {
		unit = factory->createLvl1Unit();
	}
	else {
		unit = factory->createLvl2Unit();
	}


	amountOfObjects++;
	unit->setParentField(f);

	unit->doMove(x, y);
	return unit;
}

void Field::deleteUnit(Unit*& unit) {
	amountOfObjects--;
	delete unit;
}