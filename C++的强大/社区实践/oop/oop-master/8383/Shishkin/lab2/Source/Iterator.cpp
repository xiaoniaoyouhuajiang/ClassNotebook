#include "Iterator.h"
#include "Proxy.h"

using namespace std;

Iterator::Iterator() {
	x = 0;
	y = 0;
	maxX = x - 1;
	maxY = y - 1;
	isEnd = false;
}

Iterator::~Iterator() {

}

Iterator::Iterator(Cell** cell, int x, int y) {
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
}

void Iterator::last() {
	x = maxX;
	y = maxY;
}

void Iterator::next() {
	if (x == maxX && y == maxY) isEnd = true;
	else if (x == maxX) {
		x = 0;
		y++;
	}
	else {
		x++;
	}
}

Cell* Iterator::getCell() {
	if (isEnd) return NULL;
	return &cell[x][y];
}

bool Iterator::getIsEnd() {
	return isEnd;
}

int Iterator::getX() {
	return x;
}

int Iterator::getY() {
	return y;
}

void Iterator::displayUnitData(Field& f1) {
	first();

	while (!isEnd) {
		Cell** tmp = f1.getCell();
		if (tmp[x][y].getUnit().GetValue()[0] == 'E' || tmp[x][y].getUnit().GetValue()[0] == 'M' || tmp[x][y].getUnit().GetValue()[0] == 'O')
			cout << "ѕерсонаж " << tmp[x][y].getUnit().GetValue() << " : здоровье - " << tmp[x][y].getUnit().GetHealth() << ", брон¤ - " 
			<< tmp[x][y].getUnit().GetArmor() << ", урон - " << tmp[x][y].getUnit().GetDamage() << endl;
		next();
	}
	isEnd = false;
}
