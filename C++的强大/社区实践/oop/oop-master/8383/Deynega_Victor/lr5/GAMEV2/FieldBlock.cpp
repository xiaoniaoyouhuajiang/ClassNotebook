#include <iostream> //check
#include "FieldBlock.h"
#include "Factory.h"
#include "NeutralFactory.h"

FieldBlock::FieldBlock() {
	x = 0;
	y = 0;
	landType = NULL;
	neutralPtr = NULL;
	unit = NULL;
}

FieldBlock::~FieldBlock() {}

int FieldBlock::getUnitType() {
	if (unit == nullptr) {
		return 0;
	}
	int tmp = unit->type;
	return tmp;
}


void  FieldBlock::setUnit(int type) { 
	BallistaFactory bFac;
	ArcherFactory aFac;
	DefFarmFactory dFac;
	AtFarmFactory atFac;
	BomberFactory boFac;
	GeneralBombFactory gFac;
	switch (type) {
	case 1: {
		this->unit = aFac.createUnit(x , y);
		return;
	}
	case 2: {
		this->unit = bFac.createUnit(x, y);
		return;
	}
	case 3: {
		this->unit = dFac.createUnit(x, y);
		return;
	}
	case 4: {
		this->unit = atFac.createUnit(x, y);
		return;
	}
	case 5: {
		this->unit = boFac.createUnit(x, y);
		return;
	}
	case 6: {
		this->unit = gFac.createUnit(x, y);
		return;
	}
	}
	this->unit = nullptr;
}

void FieldBlock::setLand(int type) {
	Plain* mainPlain = new Plain;
	Mountain* mainMountain = new Mountain;
	Lake* mainLake = new Lake;
	switch (type) {
	case 1: {
		this->landType = mainMountain;
		return;
	}
	case 2: {
		this->landType = mainLake;
		return;
	}
	}
	this->landType = mainPlain;
}


void FieldBlock::setNeutral(int type) {
	PosionFactory posion;
	DoubleFactory doubl;
	KnivesFactory knife;
	ArrowFactory arrow;
	switch (type) {
	case 1: {
		this->neutralPtr = posion.createObject(x, y);
		return;
	}
	case 2: {
		this->neutralPtr = knife.createObject(x, y);
		return;
	}
	case 3: {
		this->neutralPtr = arrow.createObject(x, y);
		return;
	}
	case 4: {
		this->neutralPtr = doubl.createObject(x, y);
		return;
	}
	}
		  this->neutralPtr = nullptr;
}
