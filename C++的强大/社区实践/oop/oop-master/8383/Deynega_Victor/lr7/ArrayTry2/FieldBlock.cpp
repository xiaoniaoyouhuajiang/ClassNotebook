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
	return unit->type;
}


void  FieldBlock::setUnit(int type) { 
	switch (type) {
	case 1: {
		ArcherFactory fac;
		this->unit = fac.createUnit(x , y);
		return;
	}
	case 2: {
		BallistaFactory fac;
		this->unit = fac.createUnit(x, y);
		return;
	}
	case 3: {
		DefFarmFactory fac;
		this->unit = fac.createUnit(x, y);
		return;
	}
	case 4: {
		AtFarmFactory fac;
		this->unit = fac.createUnit(x, y);
		return;
	}
	case 5: {
		BomberFactory fac;
		this->unit = fac.createUnit(x, y);
		return;
	}
	case 6: {
		GeneralBombFactory fac;
		this->unit = fac.createUnit(x, y);
		return;
	}
	case 7: {
		AssasinFactory fac;
		this->unit = fac.createUnit(x, y);
		return;
	}
	case 8: {
		BufferFactory fac;
		this->unit = fac.createUnit(x, y);
		return;
	}
	case 9: {
		WallFactory fac;
		this->unit = fac.createUnit(x, y);
		return;
	}
	case 10: {
		ImmWallFactory fac;
		this->unit = fac.createUnit(x, y);
		return;
	}
	case 11: {
		HealTowFactory fac;
		this->unit = fac.createUnit(x, y);
		return;
	}
	case 12: {
		HealUnFactory fac;
		this->unit = fac.createUnit(x, y);
		return;
	}
	case 13: {
		PudgeFactory fac;
		this->unit = fac.createUnit(x, y);
		return;
	}
	case 14: {
		ComanderFactory fac;
		this->unit = fac.createUnit(x, y);
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
