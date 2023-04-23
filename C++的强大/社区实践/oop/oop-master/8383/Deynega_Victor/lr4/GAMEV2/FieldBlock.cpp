#include <iostream> //check
#include "FieldBlock.h"
//#include "Neutral.h"

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
