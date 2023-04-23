#include "Unit.h"
#include "Field.h"
#include <iostream>
#include <cmath>
#include <map>
Unit::~Unit() {
	if (this->getParentField()) {
		Field* f = this->getParentField();
		if (this->getX() >= 0) {
			f->getTile(this->getX(), this->getY()).isOccupied = false;
			f->getTile(this->getX(), this->getY()).occupiedBy = nullptr;

		}

	}
}

int Unit::getId() {
	return id;
}

int Unit::getAttack() {
	return attack - attackDebuff + attackBuff;
}
int Unit::getHp() {
	return hp;
}
int Unit::getArmor() {
	return armor + armorBuff;
}
int Unit::getHaste() {
	return haste;
}
int Unit::getRange() {
	return range + rangeBuff;
}
int Unit::getLevel() {
	return level;
}
int Unit::getCost() {
	return cost;
}
UnitTypes Unit::getUnitType() {
	return type;
}


Field* Unit::getParentField() {
	return parentField;
}
int Unit::getX() {
	return x;
}
int Unit::getY() {

	return y;
}


std::string Unit::getUnitName() {
	if (this->getUnitType() == UnitTypes::MELEE && this->getLevel() == 1)
		return "Крестьянин";
	if (this->getUnitType() == UnitTypes::MELEE && this->getLevel() == 2)
		return "Рыцарь";
	if (this->getUnitType() == UnitTypes::RANGE && this->getLevel() == 1)
		return "Лучник";
	if (this->getUnitType() == UnitTypes::RANGE && this->getLevel() == 2)
		return "Арбалетчик";
	if (this->getUnitType() == UnitTypes::HORSEMAN && this->getLevel() == 1)
		return "Легкий кавалерист";
	if (this->getUnitType() == UnitTypes::HORSEMAN && this->getLevel() == 2)
		return "Тяжелый кавалерист";
}
void Unit::setId(int val) {
	id = val;
}

void Unit::setAttack(int val) {
	attack = val;
}
void Unit::setHp(int val) {
	hp = val;
}
void Unit::setArmor(int val) {
	armor = val;
}
void Unit::setHaste(int val) {
	haste = val;
}
void Unit::setRange(int val) {
	range = val;
}
void Unit::setLevel(int val) {
	level = val;
}
void Unit::setCost(int val) {
	cost = val;
}
void Unit::setUnitType(UnitTypes val) {
	type = val;
}




void Unit::setParentField(Field*& field){
	parentField = field;
}

bool Unit::tryToDie(Unit*& unit) {
	
	if (hp <= 0) {
		parentField->getTile(0, 0).occupiedByBase->deleteUnit(unit);
		return true;
	}
	return false;
}

bool Unit::doAttack(Unit*& target) {

	int localRange = this->range + this->rangeBuff;
	if (abs(this->x - target->x) > localRange || abs(this->y - target->y) > localRange) {
		std::cout << "Нельзя атаковать дальше чем на " << localRange << " клеток!\n";
		return false;
	}

	target->setHp(target->getHp() - this->attack + attackBuff - attackDebuff);
	return target->tryToDie(target);
}
void Unit::doMove(int x, int y) {

	if ((x >= parentField->getW()) || (y >= parentField->getH()) || x<0 || y<0) {
		std::cout << "Выход за пределы поля!\n";
		return;
	}
	if (parentField->getTile(x, y).isOccupied || parentField->getTile(x, y).isOccupiedByBase) {
		std::cout << "Клетка уже занята!\n";
		return;
	}
	int haste = this->getHaste();
	if (this->x >= 0 && (abs(this->x - x) > haste || abs(this->y - y) > haste)) {
		std::cout << "Нельзя передвинуться больше чем на " << haste <<" клеток!\n";
		return;
	}
	if (this->x >= 0) {
		
		if (parentField->getTile(this->x, this->y).isOccupiedByNeutral) {
			Unit* target = const_cast<Unit*>(this);
			parentField->getTile(this->x, this->y).occupiedByNeutral->removeEffect(target);
		}

		parentField->getTile(this->x, this->y).isOccupied = false;
		parentField->getTile(this->x, this->y).occupiedBy = nullptr;
	}
	this->x = x;
	this->y = y;
	parentField->getTile(x, y).isOccupied = true;

	parentField->getTile(x, y).occupiedBy = this;

	Unit* target = const_cast<Unit*>(this);
	parentField->getTile(x, y).terrain->doTerrainEffect(target);

	if (parentField->getTile(x, y).isOccupiedByNeutral) {
		parentField->getTile(x, y).occupiedByNeutral->applyEffect(target);
	}
}



int Unit::getAttackDebuff() {
	return attackDebuff;
}

void Unit::setAttackDebuff(int val) {
	attackDebuff = val;
}

int Unit::getArmorBuff() {
	return armorBuff;
}

void Unit::setArmorBuff(int val) {
	armorBuff = val;
}

int Unit::getAttackBuff() {
	return attackBuff;
}

void Unit::setAttackBuff(int val) {
	attackBuff = val;
}

int Unit::getRangeBuff() {
	return rangeBuff;
}

void Unit::setRangeBuff(int val) {
	rangeBuff = val;
}