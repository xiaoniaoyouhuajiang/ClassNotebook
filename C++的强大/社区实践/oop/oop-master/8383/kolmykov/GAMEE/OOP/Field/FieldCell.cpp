#include "FieldCell.h"



FieldCell::FieldCell() {
	int type = rand() % 100;
    if (type < 80) {
		land = std::shared_ptr<Land>(new CommonLand());
	}
    else if (type < 90) {
		land = std::shared_ptr<Land>(new GrassLand());
	}
	else {
		land = std::shared_ptr<Land>(new HillLand());
	}
}

FieldCell::FieldCell(const FieldCell & other)
{
	if (other.unit != nullptr) {
		unit = std::shared_ptr<Unit>(new Unit(*other.unit));
	}
	else {
		unit = nullptr;
	}
	if (other.tower != nullptr) {
		tower = std::shared_ptr<Tower>(new Tower(*other.tower));
	}
	else {
		tower = nullptr;
	}
	land = std::shared_ptr<Land>(new Land(*other.land));
}

FieldCell::FieldCell(FieldCell && other) {
	if (other.unit != nullptr) {
		unit = std::shared_ptr<Unit>(new Unit(*other.unit));
	}
	else {
		unit = nullptr;
	}
	if (other.tower != nullptr) {
		tower = std::shared_ptr<Tower>(new Tower(*other.tower));
	}
	else {
		tower = nullptr;
	}
	land = std::shared_ptr<Land>(new Land(*other.land));

	other.land = nullptr;
	other.unit = nullptr;
	other.tower = nullptr;
}

FieldCell& FieldCell::operator=(const FieldCell & other)
{
	if (other.unit != nullptr) {
		unit = std::shared_ptr<Unit>(new Unit(*other.unit));
	}
	else {
		unit = nullptr;
	}
	if (other.tower != nullptr) {
		tower = std::shared_ptr<Tower>(new Tower(*other.tower));
	}
	else {
		tower = nullptr;
	}
	land = std::shared_ptr<Land>(new Land(*other.land));
	return *this;
}

FieldCell & FieldCell::operator=(FieldCell && other)
{
	if (&other == this) {
		return *this;
	}

	if (other.unit != nullptr) {
		unit = std::shared_ptr<Unit>(new Unit(*other.unit));
	}
	else {
		unit = nullptr;
	}
	if (other.tower != nullptr) {
		tower = std::shared_ptr<Tower>(new Tower(*other.tower));
	}
	else {
		tower = nullptr;
	}
	land = std::shared_ptr<Land>(new Land(*other.land));
	return *this;
}


FieldCell::~FieldCell() {

}

void FieldCell::setUnit(std::shared_ptr<Unit> unit) {
	this->unit = unit;
}

std::shared_ptr<Unit> FieldCell::getUnit()
{
	return unit;
}

bool FieldCell::hasTower()
{
	return tower != nullptr;
}

void FieldCell::setTower(std::shared_ptr<Tower> tower) {
	this->tower = tower;
}

std::shared_ptr<Land> FieldCell::getLand()
{
	return land;
}

std::shared_ptr<Tower> FieldCell::getTower()
{
	return tower;
}

bool FieldCell::hasUnit()
{
	return unit != nullptr;
}

bool FieldCell::hasObj()
{
	return obj != nullptr;
}

std::shared_ptr<NeutralObject> FieldCell::getObj()
{
	return obj;
}

void FieldCell::setLand(std::shared_ptr<Land> land)
{
	this->land = land;
}

void FieldCell::setObj(std::shared_ptr<NeutralObject> obj)
{
	this->obj = obj;
}
