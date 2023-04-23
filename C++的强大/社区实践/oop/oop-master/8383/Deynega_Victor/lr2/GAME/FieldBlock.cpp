#include <iostream>
#include "FieldBlock.h"
//#include "Neutral.h"

FieldBlock::FieldBlock() {
	this->isEmpty = true;
	this->x = 0;
	this->y = 0;
	this->unitIndex = 0;
	this->unitType = 0;
	this->landType = NULL;
	this->neutralPtr = NULL;
	this->unit = NULL;
}

FieldBlock::~FieldBlock() {}