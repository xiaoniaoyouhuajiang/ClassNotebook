#include "Base.h"

#include "MainUnitFactory.h"
#include "MeleeFactory.h"
#include "RangeFactory.h"
#include "HorsemanFactory.h"

#include <iostream>

constexpr auto MAX_UNITS_AMOUNT = 10;

Base::Base() {

	hp = 30;

	x = -1;
	y = -1;

	parentField = nullptr;

	//units.resize(10);
	unitsCounter = 0;
}

Field* Base::getParentField() {
	return parentField;
}

void Base::setParentField(Field*& field) {
	parentField = field;
}

void Base::setBase(int x, int y) {

	if ((x >= parentField->getW()) || (y >= parentField->getH())) {
		std::cout << "Выход за пределы поля!\n";
		return;
	}

	if (this->x >= 0) {

		parentField->getTile(this->x, this->y).isOccupiedByBase = false;
		parentField->getTile(this->x, this->y).occupiedByBase = nullptr;
	}
	this->x = x;
	this->y = y;
	parentField->getTile(x, y).isOccupiedByBase = true;

	parentField->getTile(x, y).occupiedByBase = this;

}

int Base::getX() {
	return x;
}
int Base::getY() {
	return y;
}

void Base::setHp(int val) {
	hp = val;
}
int Base::getHp() {
	return hp;
}


Unit* Base::createAndSetUnit(UnitTypes type, int lvl, int x, int y) {

	if (MAX_OBJECTS_AMOUNT == this->getParentField()->getAmountOfObjects()) {
		std::cout << "Поле переполнено!\n";
		return nullptr;
	}
	if (this->getParentField()->getTile(x, y).isOccupied) {
		std::cout << "Клетка занята!\n";
		return nullptr;
	}
	if ((x >= this->getParentField()->getW()) || (y >= this->getParentField()->getH())) {
		std::cout << "Выход за пределы поля!\n";
	}
	if (MAX_UNITS_AMOUNT == unitsCounter) {
		std::cout << "Достигнуто максимальное количество юнитов!\n";
		return nullptr;
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

	this->getParentField()->raiseAmountOfObjects();
	unitsCounter++;

	unit->setId(unitsCounter);
	units.push_back(unit);

	unit->setParentField(parentField);

	unit->doMove(x, y);

	std::cout << "Создан юнит номер " << unit->getId() << "\n";

	return unit;
}

void Base::deleteUnit(Unit*& unit) {

	std::cout << "Удален юнит номер " << unit->getId() << "\n";
	int lastId = unit->getId();
	units.erase(units.begin()+unit->getId() - 1);

	this->getParentField()->lowAmountOfObjects();
	unitsCounter--;

	for (int i = lastId-1; i < unitsCounter; i++) {
		units[i]->setId(units[i]->getId() - 1);
	}

	delete unit;
}

Unit*& Base::getUnit(int id) {
	return units[id - 1];
}

Base::~Base() {

	if (unitsCounter > 0) {

		for (int i = unitsCounter-1; i >= 0; i--) {
			deleteUnit(units[i]);
		}
	}

	if (this->getParentField()) {
		Field* f = this->getParentField();
		if (this->getX() >= 0) {
			f->getTile(this->getX(), this->getY()).isOccupiedByBase = false;
			f->getTile(this->getX(), this->getY()).occupiedByBase = nullptr;

		}

	}
}