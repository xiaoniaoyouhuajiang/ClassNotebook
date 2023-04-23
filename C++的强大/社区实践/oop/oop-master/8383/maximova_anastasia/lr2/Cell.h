#pragma once
#include "Object.h"
#include "Landscape.h"
#include "NeutralObject.h"
#include "Base.h"

class Cell {
private:
	Unit* unit;
	Landscape* landscape;
	NeutralObject* neutralObject;
	Base* base;

public:
	Cell();
	void setUnit(Unit* unit);
	void setLand(Landscape* landscape);
	void setNeutralObject(NeutralObject* neutralObject);
	void setBase(Base* base);

	Unit* getUnit();
	Landscape* getLand();
	NeutralObject* getNeutralObject();
	Base* getBase();
};