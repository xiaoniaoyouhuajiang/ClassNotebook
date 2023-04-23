#pragma once
#include "Armor.h"
class HeavyArmor :
	public Armor
{
public:
	HeavyArmor();
	HeavyArmor(const HeavyArmor& other);
	~HeavyArmor();
};

