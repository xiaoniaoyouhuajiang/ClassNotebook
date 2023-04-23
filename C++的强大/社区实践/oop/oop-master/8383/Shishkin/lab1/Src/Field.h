#pragma once

#include "Warrior.h"
#include "Orcs.h"
#include "Men.h"
#include "Elfs.h"

using namespace std;

class Field {
public:
	Field();
	Field(int a);
	~Field();
	Field(const Field& f);
	Field(Field&& f);
	void mas();
	void print();
	void init(int numOfOrcs, int numOfElfs, int numOfMens);
	void moving(string character, int direction);
	string check(string character);
	void add(string character);
	void del(string character);

private:
	int size, x0, y0;
	Warrior** cell;
};
