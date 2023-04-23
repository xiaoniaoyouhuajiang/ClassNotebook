#include <GAME/engine/terrains/SeaTerrain.hpp>
#include <GAME/engine/Unit.hpp>

SeaEffect::SeaEffect() : TerrainEffect(SEA_EFFECT, SEA_TERRAIN) {}

float SeaEffect::transformAttackRange(float range) const {
	return 0;
}

float SeaEffect::transformSpeed(float speed) const {
	return std::max(speed * 0.5f, 1.0f);
}

SeaTerrain::SeaTerrain() : Terrain(SEA_TERRAIN) {}
SeaTerrain::SeaTerrain(Cell* cell) : Terrain(SEA_TERRAIN, cell) {}

void SeaTerrain::onAttachUnit(Unit& unit) {
	unit.addEffect(shared_ptr<Effect>(new SeaEffect()));
}
