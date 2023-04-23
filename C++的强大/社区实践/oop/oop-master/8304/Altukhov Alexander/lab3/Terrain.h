#pragma once
#include "ITerrain.h"
#include "Unit.h"
class Unit;
enum class TerrainTypes {
	FIELD, FOREST, SWAMP
};

class Terrain: public ITerrain {

	TerrainTypes type;

public:

	Terrain() = default;
	~Terrain() = default;
	TerrainTypes getTerrainType();  
	void setTerrainType(TerrainTypes type);
	virtual void doTerrainEffect(Unit*& target) = 0;


};

