#pragma once

#include "Terrain.h"


class FieldTerrain :public Terrain {

public:
	FieldTerrain();
	virtual void doTerrainEffect(Unit*& target);
};

