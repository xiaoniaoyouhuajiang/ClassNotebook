#pragma once

//#include "Field.h"
#include "Warrior.h"

class Field;
//class Warrior;

class Mediator {
public:
	Mediator(Field* f);
	void attack(Warrior w1, Warrior& w2);  //атака w1 на w2

private:
	Field* f;
};
