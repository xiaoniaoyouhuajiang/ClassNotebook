#pragma once
#include "Unit.h"
class Unit;
struct Tile {

	
	int x;
	int y;
	bool isOccupied;
	Unit* occupiedBy;

	Tile() = default;
	Tile(int x, int y) :x(x), y(y), isOccupied(false), occupiedBy(nullptr) {}
	Tile(int x, int y, bool isOccupied, Unit*& occupiedBy) :x(x), y(y), isOccupied(isOccupied), occupiedBy(occupiedBy) {}

};

