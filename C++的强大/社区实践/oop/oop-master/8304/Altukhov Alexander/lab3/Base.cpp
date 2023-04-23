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
	lastId = 1;
	parentField = nullptr;

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
	bool copy = !(x == 0 && y == 0);
	
	if (copy) {
		if (this->getParentField()->getTile(x, y).isOccupied) {
			std::cout << "Клетка занята!\n";
			return nullptr;
		}
	}
	else {
		//доступно создание на клетках рядом с базой: 0,1 1,0 1,1
		if (!this->getParentField()->getTile(0, 1).isOccupied) {
			y = 1;
		}
		else if (!this->getParentField()->getTile(1, 0).isOccupied) {
			x = 1;
		}
		else if (!this->getParentField()->getTile(1, 1).isOccupied) {
			x = 1;
			y = 1;
		}
		else {
			std::cout << "Освободите клетки рядом с базой чтобы создавать юнитов!\n";
			return nullptr;
		}

		
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

	unit->setId(lastId);
	units[lastId++] = unit;

	unit->setParentField(parentField);

	unit->doMove(x, y);

	std::cout << "Создан юнит номер " << unit->getId() << "\n";

	return unit;
}

void Base::deleteUnit(Unit*& unit) {

	int myId = unit->getId();
	delete unit;
	units.erase(myId);

	std::cout << "Удален юнит номер " << myId << "\n";

	this->getParentField()->lowAmountOfObjects();

	unitsCounter--;
}

std::map<int, Unit*>::iterator Base::deleteUnit(std::map<int, Unit*>::iterator it) {


	int myId = it->second->getId();
	delete it->second;
	auto nextIt = units.erase(it);

	std::cout << "Удален юнит номер " << myId << "\n";

	this->getParentField()->lowAmountOfObjects();

	unitsCounter--;
	return nextIt;
}

Unit* Base::getUnit(int id) {

	auto it = units.find(id);
	if (it == units.end())
		return nullptr;

	return units[id];
}

bool Base::writeUnitInfo(int id) {
	auto it = units.find(id);
	if (it == units.end())
		return false;
	std::cout << "--------------------\n";
	std::cout << "Id: " << it->first << "\n";
	std::cout << "Имя: " << it->second->getUnitName() << "\n";
	std::cout << "Здоровье: " << it->second->getHp() << "\n";
	std::cout << "Атака: " << it->second->getAttack() << "\n";
	std::cout << "Скорость: " << it->second->getHaste() << "\n";
	std::cout << "Дальность: " << it->second->getRange() << "\n";
	std::cout << "Броня: " << it->second->getArmor() << "\n";
	std::cout << "--------------------\n";
	return true;
}

Base::~Base() {

	if (unitsCounter > 0) {

		//std::cout << units.size() << "\n";
		auto nextIt = units.begin();
		for (auto it = units.begin(); it != units.end(); it = nextIt) {
			nextIt = deleteUnit(it);

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

void Base::writeBaseState() {

	std::cout << "Здоровье базы: " << this->getHp() << "\n";
	std::cout << "Контроллирует юнитов: " << unitsCounter << "\n";
	for (auto it = units.begin(); it != units.end(); it++) {
		std::cout << "Id: " << it->first << ", " << it->second->getUnitName() << "\n";
	}
}