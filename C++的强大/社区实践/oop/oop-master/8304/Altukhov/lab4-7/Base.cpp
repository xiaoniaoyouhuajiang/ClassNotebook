#include "Base.h"

#include "MainUnitFactory.h"
#include "MeleeFactory.h"
#include "RangeFactory.h"
#include "HorsemanFactory.h"

#include <iostream>

constexpr auto MAX_UNITS_AMOUNT = 10;

Base::Base(int player) {

	hp = 30;

	x = -1;
	y = -1;
	lastId = 1;
	parentField = nullptr;

	unitsCounter = 0;
	this->player = player;
}

Field* Base::getParentField() {
	return parentField;
}

void Base::setParentField(Field*& field) {
	parentField = field;
}

void Base::setBase(int x, int y) {

	if ((x >= parentField->getW()) || (y >= parentField->getH())) {
		//std::cout << "Выход за пределы поля!\n";
		//log << (std::string)"Выход за пределы поля!\n";
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

int Base::getPlayer()
{
	return player;
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
void Base::setMoney(int val)
{
	money = val;
}
int Base::getMoney()
{
	return money;
}
int Base::getHp() {
	return hp;
}


Unit* Base::createAndSetUnit(UnitTypes type, int lvl, int x, int y) {

	if (MAX_OBJECTS_AMOUNT == this->getParentField()->getAmountOfObjects()) {
		//std::cout << "Поле переполнено!\n";
		log << (std::string)"Поле переполнено!\n";
		return nullptr;
	}
	bool copy = !(x == 0 && y == 0);
	
	if (copy) {
		if (this->getParentField()->getTile(x, y).isOccupied) {
			//std::cout << "Клетка занята!\n";
			log << (std::string)"Клетка занята!\n";
			return nullptr;
		}
	}
	else {
		//доступно создание на клетках рядом с базой: 0,1 1,0 1,1
		if (player == 1) {
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
				//std::cout << "Освободите клетки рядом с базой чтобы создавать юнитов!\n";
				log << (std::string)"Освободите клетки рядом с базой чтобы создавать юнитов!\n";
				return nullptr;
			}
		}
		else if (player == 2) {
			if (!this->getParentField()->getTile(this->getParentField()->getW()-1, this->getParentField()->getH()-1-1).isOccupied) {
				x = this->getParentField()->getW() - 1;
				y = this->getParentField()->getH() - 1 - 1;
			}
			else if (!this->getParentField()->getTile(this->getParentField()->getW() - 1 -1 , this->getParentField()->getH() - 1).isOccupied) {
				x = this->getParentField()->getW() - 1 - 1;
				y = this->getParentField()->getH() - 1;
			}
			else if (!this->getParentField()->getTile(this->getParentField()->getW() - 1 - 1, this->getParentField()->getH() - 1 - 1).isOccupied) {
				x = this->getParentField()->getW() - 1 - 1;
				y = this->getParentField()->getH() - 1 - 1;
			}
			else {
				//std::cout << "Освободите клетки рядом с базой чтобы создавать юнитов!\n";
				log << (std::string)"Освободите клетки рядом с базой чтобы создавать юнитов!\n";
				return nullptr;
			}
		}

		
	}
	if ((x >= this->getParentField()->getW()) || (y >= this->getParentField()->getH())) {
		//std::cout << "Выход за пределы поля!\n";
		log << (std::string)"Выход за пределы поля!\n";
	}
	if (MAX_UNITS_AMOUNT == unitsCounter) {
		//std::cout << "Достигнуто максимальное количество юнитов!\n";
		log << (std::string)"Достигнуто максимальное количество юнитов!\n";
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
	if (unit->getCost() > money && !copy) {
		log << "Не хватает денег на юнита: " + std::to_string(std::abs(unit->getCost() - money)) + " монет.\n";
		delete unit;
		return nullptr;
	}
	this->getParentField()->raiseAmountOfObjects();
	unitsCounter++;
	if (!copy)
		money -= unit->getCost();
	unit->setId(lastId);
	unit->addLog(log);
	units[lastId++] = unit;

	unit->setParentField(parentField);
	Base* parentBase = const_cast<Base*>(this);
	unit->setParentBase(parentBase, this->player);
	unit->doMove(x, y);
	log << ("Создан юнит номер " + std::to_string(unit->getId()) + "\n");
	//std::cout << "Создан юнит номер " << unit->getId() << "\n";

	return unit;
}





void Base::deleteUnit(Unit*& unit) {

	int myId = unit->getId();
	delete unit;
	units.erase(myId);

	log << ("Удален юнит номер " + std::to_string(myId) + "\n");
	//std::cout << "Удален юнит номер " << myId << "\n";

	this->getParentField()->lowAmountOfObjects();

	unitsCounter--;
}

std::map<int, Unit*>::iterator Base::deleteUnit(std::map<int, Unit*>::iterator it) {


	int myId = it->second->getId();
	delete it->second;
	auto nextIt = units.erase(it);

	//std::cout << "Удален юнит номер " << myId << "\n";
	log << ("Удален юнит номер " + std::to_string(myId) + "\n");

	this->getParentField()->lowAmountOfObjects();

	unitsCounter--;
	return nextIt;
}


void Base::addLog(ProxyLog* log)
{
	this->log = log;
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
	//std::cout << "--------------------\n";
	//std::cout << "Id: " << it->first << "\n";
	//std::cout << "Имя: " << it->second->getUnitName() << "\n";
	//std::cout << "Здоровье: " << it->second->getHp() << "\n";
	//std::cout << "Атака: " << it->second->getAttack() << "\n";
	//std::cout << "Скорость: " << it->second->getHaste() << "\n";
	//std::cout << "Дальность: " << it->second->getRange() << "\n";
	//std::cout << "Броня: " << it->second->getArmor() << "\n";
	//std::cout << "--------------------\n";
	log << (std::string)"--------------------\n";

	log << "Id: " + std::to_string(it->first) + "\n";
	log << "Имя: " + it->second->getUnitName() + "\n";
	log << "Здоровье: " + std::to_string(it->second->getHp()) + "\n";
	log << "Атака: " + std::to_string(it->second->getAttack()) + "\n";
	log << "Скорость: " + std::to_string(it->second->getHaste()) + "\n";
	log << "Дальность: " + std::to_string(it->second->getRange()) + "\n";
	log << "Броня: " + std::to_string(it->second->getArmor()) + "\n";

	log << (std::string)"--------------------\n";
	return true;
}
bool Base::tryToDie() {
	if (hp <= 0) {
		return true;
	}
	return false;
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
void Base::prepareToNextTurn() {

	
	int newMoney = 0;
	for (int i = 0; i < this->getParentField()->getW(); i++) {

		for (int j = 0; j < this->getParentField()->getH(); j++) {
			//std::cout << i << " " << j << " " << this->getParentField()->getTile(x, y).capturedBy << "\n";
			if (this->getParentField()->getTile(i, j).capturedBy == player) {
				newMoney++;
			}
		}
	}
	log << "Доход игрока " + std::to_string(player) + ": " + std::to_string(newMoney) + "\n";
	this->setMoney(this->getMoney() + newMoney);
	if (unitsCounter > 0) {


		for (auto it = units.begin(); it != units.end(); it++) {
			it->second->resetAttacked();
			it->second->resetMoved();

		}

	}
	addTurn();
}

int Base::getTurn() {
	return turn;
}
void Base::addTurn()
{
	turn++;
}
void Base::writeBaseState() {

	//std::cout << "Здоровье базы: " << this->getHp() << "\n";
	log << "Здоровье базы: " + std::to_string(this->getHp()) + "\n";
	log << "Деньги: " + std::to_string(this->getMoney()) + "\n";
	log << "Ход: " + std::to_string(this->getTurn()) + "\n";
	//std::cout << "Контроллирует юнитов: " << unitsCounter << "\n";
	log << "Контроллирует юнитов: " + std::to_string(unitsCounter) + "\n";
	for (auto it = units.begin(); it != units.end(); it++) {
		//std::cout << "Id: " << it->first << ", " << it->second->getUnitName() << "\n";
		log << "Id: " + std::to_string(it->first) + ", " + it->second->getUnitName() + "\n";
	}
}



void Base::fillMemento(Memento*& snapshot, bool myTurn) {

	if (myTurn) {
		snapshot->whatPlayerTurn = player;

	}
	if (player == 1) {
		snapshot->hp1 = hp;
		snapshot->money1 = money;
		snapshot->turn1 = turn;
		snapshot->units1.clear();
		for (auto it = units.begin(); it != units.end(); it++) {
			int type = it->second->getUnitType() == UnitTypes::MELEE ? 1 : it->second->getUnitType() == UnitTypes::RANGE ? 2 : it->second->getUnitType() == UnitTypes::HORSEMAN ? 3 : 0;
			snapshot->units1.push_back({ it->second->getX(), it->second->getY(), type, it->second->getLevel(), it->second->getHp(), it->second->getMoved(), it->second->getAttacked() });

		}
	}

	if (player == 2) {
		snapshot->hp2 = hp;
		snapshot->money2 = money;
		snapshot->turn2 = turn;
		snapshot->units2.clear();
		for (auto it = units.begin(); it != units.end(); it++) {
			int type = it->second->getUnitType() == UnitTypes::MELEE ? 1 : it->second->getUnitType() == UnitTypes::RANGE ? 2 : it->second->getUnitType() == UnitTypes::HORSEMAN ? 3 : 0;
			snapshot->units2.push_back({ it->second->getX(), it->second->getY(), type, it->second->getLevel(), it->second->getHp() });

		}
	}
}

void Base::deleteUnits() {
	if (unitsCounter > 0) {

		//std::cout << units.size() << "\n";
		auto nextIt = units.begin();
		for (auto it = units.begin(); it != units.end(); it = nextIt) {
			nextIt = deleteUnit(it);

		}

	}
}

void Base::newBase(Memento*& snapshot, int myNum) {
	std::vector<Memento::UnitInfo> vec;
	lastId = 1;
	if (myNum == 1) {

		hp = snapshot->hp1;
		money = snapshot->money1;
		turn = snapshot->turn1;
		vec = snapshot->units1;
	}
	else if (myNum == 2) {
		hp = snapshot->hp2;
		money = snapshot->money2;
		turn = snapshot->turn2;
		vec = snapshot->units2;
	}

	for (int i = 0; i < vec.size(); i++) {
		UnitTypes type = UnitTypes::MELEE;
		if (vec[i].type == 1) {
			type = UnitTypes::MELEE;
		}
		else if (vec[i].type == 2) {
			type = UnitTypes::RANGE;
		}
		else if (vec[i].type == 3) {
			type = UnitTypes::HORSEMAN;
		}

		auto unit = createAndSetUnit(type, vec[i].level, vec[i].x, vec[i].y);
		if (unit) {
			unit->setHp(vec[i].hp);
			unit->setAttacked(vec[i].canAttack);
			unit->setMoved(vec[i].canMove);
		}
	}
}