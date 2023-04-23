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
	void addUnit(Point p);
	void forgetAbout(Point p);

	size_t getMaxUnitsCnt() const;
	size_t getNowUnitsCnt() const;
	void update(Point from, Point to);
	std::vector<Point> notify();
};