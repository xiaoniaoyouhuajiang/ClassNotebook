#pragma once
#include "Terrain.h"

class Terrain;
class ForestTerrain : public Terrain {

public:
	ForestTerrain();
	virtual void doTerrainEffect(Unit*& target);
};

