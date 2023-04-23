#include "Iterator.h"

using namespace std;

Iterator::Iterator(Warrior** cell, int x, int y) {
	this->cell = cell;
	this->x = 0;
	this->y = 0;
	maxX = x - 1;
	maxY = y - 1;
	isEnd = false;
}

void Iterator::first() {
	x = 0;
	y = 0;

	cout << x << " " << y << endl;
}

void Iterator::last() {
	x = maxX;
	y = maxY;
	cout << x << " " << y << endl;
}

void Iterator::next() {
	if (x == maxX && y == maxY) isEnd = true;
	else if (x == maxX) {
		x = 0;
		y++;
		cout << x << " " << y << endl;
	}
	else {
		x++;
		cout << x << " " << y << endl;
	}
}

Warrior* Iterator::getCell() {
	if (isEnd) return NULL;
	return &cell[x][y];
}
