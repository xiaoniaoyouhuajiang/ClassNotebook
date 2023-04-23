#include "SwampTerrain.h"

SwampTerrain::SwampTerrain() {
	setTerrainType(TerrainTypes::SWAMP);
}

void SwampTerrain::doTerrainEffect(Unit*& target) {
	target->setHp(target->getHp() - 1);
	target->tryToDie(target);
}