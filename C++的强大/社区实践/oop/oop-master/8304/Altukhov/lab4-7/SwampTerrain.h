#pragma once
#include "Terrain.h"
class Unit;
class SwampTerrain :
	public Terrain
{
public:
	SwampTerrain();
	virtual void doTerrainEffect(Unit*& target);
};
