#pragma once
#include "Unit.h" 
#include <memory>
#include "Tower.h"
#include "CommonLand.h"
#include "GrassLand.h"
#include "HillLand.h"
#include "ProxyLand.h"
#include <cstdlib>
#include <ctime>
#include "NeutralObject.h"


class FieldCell
{
private:
	std::shared_ptr <Unit> unit;
	std::shared_ptr<Tower> tower;
	std::shared_ptr<Land> land;
	std::shared_ptr<NeutralObject> obj;


public:
	FieldCell();
	FieldCell(const FieldCell& other);
	FieldCell(FieldCell&& other);
	FieldCell& operator=(const FieldCell& other);
	FieldCell& operator=(FieldCell&& other);
	~FieldCell();
	void setUnit(std::shared_ptr<Unit> unit);
	std::shared_ptr<Unit> getUnit();
	bool hasTower();
	void setTower(std::shared_ptr<Tower> tower);
	std::shared_ptr<Land> getLand();
	std::shared_ptr<Tower> getTower();
	bool hasUnit();
	bool hasObj();
	std::shared_ptr<NeutralObject> getObj();
	void setLand(std::shared_ptr<Land> land);
	void setObj(std::shared_ptr<NeutralObject> obj);
};

