#pragma once
#include "ArmorObject.h"
#include "LargeArmorAffectBehavior.h"
class LargeArmorObject :
	public ArmorObject
{
public:
	LargeArmorObject();
	~LargeArmorObject();
    std::string getPath();
};

