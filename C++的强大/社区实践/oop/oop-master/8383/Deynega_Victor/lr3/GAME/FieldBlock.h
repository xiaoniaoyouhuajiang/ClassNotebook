#pragma once
#include "Landscape.h"
#include "Neutral.h"
#include "Units.h"

class FieldBlock {
public:
	int x;
	int y;
	bool isEmpty;
	int unitType;
	int unitIndex;
	Unit* unit;
	NeutralObject* neutralPtr;
	Landscape* landType;
	FieldBlock();
	~FieldBlock();
};