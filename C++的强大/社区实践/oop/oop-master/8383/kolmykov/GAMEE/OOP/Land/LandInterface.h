#pragma once
#include <memory>


class Unit;

class LandInterface
{
public:
	LandInterface();
	~LandInterface();
	virtual void bufUnit(std::shared_ptr<Unit> unit) = 0;
};

