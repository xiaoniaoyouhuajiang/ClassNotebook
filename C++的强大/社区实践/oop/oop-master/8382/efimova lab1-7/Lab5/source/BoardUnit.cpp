#include "BoardUnit.h"

unsigned int BoardUnit::unitCount = 0;
unsigned int BoardUnit::idCount = 0;

unsigned int BoardUnit::getUnitCount() {
	return unitCount;
}

BoardUnit::BoardUnit() {
	unitCount++;
	idCount++;
	_id = idCount;
}

BoardUnit::~BoardUnit() {
	unitCount--;
}

unsigned int BoardUnit::getID() {
	return _id;
}