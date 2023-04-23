#pragma once
#include "Weapon.h"
class Bat :
	public Weapon
{
public:
	Bat();
	Bat(const Bat& other);
	~Bat();
};

