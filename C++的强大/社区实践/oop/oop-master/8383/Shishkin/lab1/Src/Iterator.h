#pragma once

#include "Warrior.h"

class Iterator {
public:
	Iterator(Warrior** cell, int x, int y);
	void first();
	void last();
	void next();
	Warrior* getCell();

private:
	int x, y;
	int maxX, maxY;
	bool isEnd;
	Warrior** cell;
};