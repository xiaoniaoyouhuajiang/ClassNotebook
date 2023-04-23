#include "Base.h"

Base::Base(int healthBase, int maxUnits, int maxUnitsSt, int view, char name) {
	this->healthBase = healthBase;
	this->counterUnits = 0;         //текущий счетчик юнитов
	this->maxUnits = maxUnits;      //максимальное кол-во юнитов, которое мб создано за один раз после старта игры
	this->maxUnitsSt = maxUnitsSt;  //максимальное кол-во юнитов в команде, которое может быть создано в начале игры
	setView(view);
	setName(name);
}

void Base::setHealthBase(int healthBase) { 
	this->healthBase = healthBase;
}

void Base::setCounterUnits(int counterUnits) { 
	this->counterUnits = counterUnits;
}

int Base::getCounterUnits() {
	return counterUnits;
}

int Base::getmaxUnitsSt() {
	return maxUnitsSt;
}

int Base::getMaxUnits() {
	return maxUnits;
}

int Base::getHealthBase() {
	return healthBase;
}

Base& Base::operator -=(Unit& unit) {
	this->setHealthBase(this->getHealthBase() - unit.getDamage());
	return *this;
}

BasePeople::BasePeople(int coef) : Base(15000, 4, 12, 9, (char)203) {
	this->maxUnits *= coef;
	this->maxUnitsSt *= coef;
}

BaseMonster::BaseMonster(int coef) : Base(10000, 2, 6, 10, (char)204) {
	this->maxUnits *= coef;
	this->maxUnitsSt *= coef;
}

BaseHero::BaseHero(int coef) : Base(10000, 2, 6, 11, (char)195) {
	this->maxUnits *= coef;
	this->maxUnitsSt *= coef;
}