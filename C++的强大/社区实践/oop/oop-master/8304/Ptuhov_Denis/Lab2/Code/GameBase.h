#pragma once
#include <memory>
#include <iostream>
#include "Resourses.h"
#include "UnitBase.h"

struct GameBase
{
private:
	Hp hp;
	size_t units_cnt = 0;
	std::vector<Point> units;

public:
	GameBase();
	void setUnitsCnt(size_t n);
	bool addUnit(Point p);
	void forgetAbout(Point p);
	std::vector<Point> notify();
};