#include "FieldTerrain.h"


FieldTerrain::FieldTerrain() {
	setTerrainType(TerrainTypes::FIELD);
}

void FieldTerrain::doTerrainEffect(Unit*& target) {
	target->setAttackDebuff(0);
}