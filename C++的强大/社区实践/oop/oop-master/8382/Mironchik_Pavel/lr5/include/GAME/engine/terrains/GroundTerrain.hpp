#pragma once

#include <GAME/engine/Terrain.hpp>

class GroundTerrain : public Terrain {
public:
	GroundTerrain(istream& is, InObjectsTable& table) : Terrain(is, table) {}

	GroundTerrain() : Terrain(GROUND_TERRAIN) {}
	GroundTerrain(Cell* cell) : Terrain(GROUND_TERRAIN, cell) {}
};