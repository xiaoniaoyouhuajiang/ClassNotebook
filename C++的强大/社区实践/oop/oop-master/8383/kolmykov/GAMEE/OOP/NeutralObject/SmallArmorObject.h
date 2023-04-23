#pragma once
#include "ArmorObject.h"
#include "SmallArmorAffectBehavior.h"
class SmallArmorObject :
	public ArmorObject
{
public:
	SmallArmorObject();
	~SmallArmorObject();
    std::string getPath();
	//void operator+=(Unit& unit);
};

