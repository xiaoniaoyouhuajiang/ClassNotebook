#pragma once
#include <memory>
#include "Resourses.h"
#include "UnitBase.h"

struct GameBase
{
	GameBase();
	void setUnitsCnt(size_t n);
	void createUnit(std::shared_ptr<UnitBase>& unit, Point p);
	void forgetAbout(Point p);
	void notify();

private:
	struct CreatedUnit
	{
		Point p;
		std::shared_ptr<UnitBase>* unit = nullptr;
	};

	Hp hp;
	size_t units_cnt = 0;
	std::vector<CreatedUnit> units;
};