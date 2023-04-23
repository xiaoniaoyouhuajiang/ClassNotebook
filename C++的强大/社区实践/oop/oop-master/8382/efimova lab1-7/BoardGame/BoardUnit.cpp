#include "BoardUnit.h"

unsigned int BoardUnit::unitCount = 0;

unsigned int BoardUnit::getUnitCount() {
	return unitCount;
}

BoardUnit::BoardUnit() {
	unitCount++;
}

BoardUnit::~BoardUnit() {
	unitCount--;
}