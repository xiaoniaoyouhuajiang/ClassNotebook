#pragma once //check
#include "Landscape.h"
#include "Neutral.h"
#include "Units.h"

class FieldBlock {
public:
	int x;
	int y;
	Unit* unit;
	NeutralObject* neutralPtr;
	Landscape* landType;
	int getUnitType();
	void setUnit(int type);
	void setNeutral(int type);
	void setLand(int type);
	FieldBlock();
	~FieldBlock();
};
