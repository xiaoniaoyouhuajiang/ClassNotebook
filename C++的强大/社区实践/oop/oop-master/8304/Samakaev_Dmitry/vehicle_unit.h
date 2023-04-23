#pragma once
#include <iostream>
#include "unit_base.h"



class Vehicle_unit : public Unit {

};

class Siege_tower : public Vehicle_unit {
public:
	Siege_tower();
};

class Catapult : public Vehicle_unit {
public:
	Catapult();
};