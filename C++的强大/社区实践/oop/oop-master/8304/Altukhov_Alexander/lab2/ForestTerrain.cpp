#include "ForestTerrain.h"

ForestTerrain::ForestTerrain() {
	setTerrainType(TerrainTypes::FOREST);
}

void ForestTerrain::doTerrainEffect(Unit*& target) {
	target->setAttackDebuff(1);
}