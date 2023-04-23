#include "Unit.h"
#include "Field.h"
#include <iostream>

Unit::~Unit() {
	if (this->getParentField()) {
		Field* f = this->getParentField();
		if (this->getX() >= 0) {
			f->getTile(this->getX(), this->getY()).isOccupied = false;
			f->getTile(this->getX(), this->getY()).occupiedBy = nullptr;

		}

	}
}

int Unit::getAttack() {
	return attack;
}
int Unit::getHp() {
	return hp;
}
int Unit::getArmor() {
	return armor;
}
int Unit::getHaste() {
	return haste;
}
int Unit::getRange() {
	return range;
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



void Unit::doAttack() {

}
void Unit::doMove(int x, int y) {

	if ((x >= parentField->getW()) || (y >= parentField->getH())) {
		std::cout << "Выход за пределы поля!\n";
		return;
	}

	if (this->x >= 0) {
		
		parentField->getTile(this->x, this->y).isOccupied = false;
		parentField->getTile(this->x, this->y).occupiedBy = nullptr;
	}
	this->x = x;
	this->y = y;
	parentField->getTile(x, y).isOccupied = true;

	parentField->getTile(x, y).occupiedBy = this;
}