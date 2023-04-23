#pragma once //check
#include "Landscape.h"
#include "Neutral.h"
#include "Units.h"
//#include "Base.h"

class FieldBlock {
public:
	int x;
	int y;
	Unit* unit;
	NeutralObject* neutralPtr;
	Landscape* landType;
  //  Base* base;
	int getUnitType();
	void setUnit(int type);
	void setNeutral(int type);
	void setLand(int type);
	FieldBlock();
	~FieldBlock();
};
