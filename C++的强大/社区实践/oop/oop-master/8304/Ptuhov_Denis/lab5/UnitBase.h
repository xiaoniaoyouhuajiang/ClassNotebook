#pragma once
#include <random>
#include <memory>
#include <iostream>
#include "Resourses.h"
#include "NtrkObj.h"
#include "Subscriber.h"

struct UnitBase : Subscriber
{
	virtual takeDamageResult takeDamage(size_t damageSize) = 0;
	void increaseDamage(size_t n);

	void setPoint(Point p);
	void tellAboutMe();
	void operator()(std::shared_ptr<NtrlObj> ntrl);
	void operator()(LandscapeInfo effect);
	void update();

	Point p;
	Damage damage;
	Hp hp;
	size_t range;
	size_t cost;
	char name;
};