#pragma once
#include "Armor.h"
class NoArmor :
	public Armor
{
public:
	NoArmor();
	NoArmor(const NoArmor& other);
	~NoArmor();
};

