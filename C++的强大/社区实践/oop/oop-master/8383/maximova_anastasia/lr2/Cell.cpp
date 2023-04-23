#include "Cell.h"

Cell::Cell() {
	unit = nullptr;
	landscape = nullptr;
	neutralObject = nullptr;
	base = nullptr;
}

void Cell::setUnit(Unit* unit) {
	this->unit = unit;
}

void Cell::setLand(Landscape* landscape) {
	this->landscape = landscape;
}

void Cell::setNeutralObject(NeutralObject* neutralObject) {
	this->neutralObject = neutralObject;
}

void Cell::setBase(Base* base) {
	this->base = base;
}

Unit* Cell::getUnit() {
	return unit;
}

Landscape* Cell::getLand() {
	return landscape;
}

NeutralObject* Cell::getNeutralObject() {
	return neutralObject;
}

Base* Cell::getBase() {
	return base;
}