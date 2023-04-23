#pragma once
//#include "Unit.h"
#include "Base.h"

#include "ITerrain.h"
#include "Terrain.h"
#include "FieldTerrain.h"
#include "ForestTerrain.h"
#include "SwampTerrain.h"

class Base;
class Unit;

#include "NeutralObject.h"
#include "TowerNeutral.h"
#include "WeaponryNeutral.h"
#include "CannonNeutral.h"
#include "ShrineNeutral.h"


class NeutralObject;
//class ITerrain;
class Terrain;
struct Tile {

	
	int x;
	int y;

	Terrain* terrain;
	bool isOccupied;//unit
	Unit* occupiedBy;//unit

	bool isOccupiedByBase;
	Base* occupiedByBase;

	bool isOccupiedByNeutral;
	NeutralObject* occupiedByNeutral;
	//neutral*

	Tile() = default;
	Tile(int x, int y) :x(x), y(y), isOccupied(false), occupiedBy(nullptr), isOccupiedByBase(false), occupiedByBase(nullptr), isOccupiedByNeutral(false), occupiedByNeutral(nullptr){
		int random = rand() % 3 + 1;
		if (random == 1)
			terrain = new FieldTerrain;
		else if (random == 2)
			terrain = new ForestTerrain;
		else if (random == 3)
			terrain = new SwampTerrain;

		if ((x == 8) && (y == 3)) {
			isOccupiedByNeutral = true;
			occupiedByNeutral = new TowerNeutral;

		}
		if ((y == 6) && (x == 7)) {
			isOccupiedByNeutral = true;
			occupiedByNeutral = new WeaponryNeutral;

		}
		if ((x == 2) && (y == 4)) {
			isOccupiedByNeutral = true;
			occupiedByNeutral = new CannonNeutral;

		}
		if ((y == 7) && (x == 4)) {
			isOccupiedByNeutral = true;
			occupiedByNeutral = new ShrineNeutral;

		}
	}
	Tile(int x, int y, Terrain*& terrain, bool isOccupied, Unit*& occupiedBy, bool isOccupiedByNeutral, NeutralObject* occupiedByNeutral) :x(x), y(y), terrain(terrain), isOccupied(isOccupied), occupiedBy(occupiedBy), isOccupiedByBase(false), occupiedByBase(nullptr), isOccupiedByNeutral(isOccupiedByNeutral), occupiedByNeutral(occupiedByNeutral){}
	Tile(int x, int y, Terrain*& terrain, bool isOccupiedByBase, Base*& occupiedByBase, bool isOccupiedByNeutral, NeutralObject* occupiedByNeutral) :x(x), y(y), terrain(terrain), isOccupied(false), occupiedBy(nullptr), isOccupiedByBase(isOccupiedByBase), occupiedByBase(occupiedByBase), isOccupiedByNeutral(isOccupiedByNeutral), occupiedByNeutral(occupiedByNeutral) {}
};

