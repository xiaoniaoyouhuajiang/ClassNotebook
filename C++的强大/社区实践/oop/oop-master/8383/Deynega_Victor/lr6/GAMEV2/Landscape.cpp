#include "Landscape.h" //check


Landscape::Landscape() {}

Mountain::Mountain() {}

int Mountain:: getType() {
	return 1;
}

Lake::Lake() {}

int Lake::getType() {
	return 2;
}

Plain::Plain() {}

int Plain::getType() {
	return 0;
}

