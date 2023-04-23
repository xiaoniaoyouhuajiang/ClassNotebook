#include <GAME/engine/terrains/LavaTerrain.hpp>
#include <GAME/engine/Unit.hpp>
#include <GAME/engine/GameBoard.hpp>
#include <GAME/engine/Cell.hpp>
#include <iostream>

LavaEffect::LavaEffect(istream& is, InObjectsTable& table) : TerrainEffect(is, table) {
	Serializer::readFloat(is, &_damage);
}

void LavaEffect::writeObject(ostream& os, OutObjectsTable& table) {
	TerrainEffect::writeObject(os, table);
	Serializer::writeFloat(os, &_damage);
}

LavaEffect::LavaEffect(): TerrainEffect(LAVA_EFFECT, LAVA_TERRAIN) {}

void LavaEffect::onAttach(Unit& object) {
	TerrainEffect::onAttach(object);
	object.getBoard()->getController().damageUnit(object, _damage);
}

void LavaEffect::onDetach() {
	TerrainEffect::onDetach();
}

void LavaEffect::onOriginMoved(Unit& origin, sf::Vector2i& from, sf::Vector2i& to) {
	TerrainEffect::onOriginMoved(origin, from, to);

	if (isAttached()) {
		_damage *= DAMAGE_MULT;
		origin.getBoard()->getController().damageUnit(origin, _damage);
	}
}


LavaTerrain::LavaTerrain(istream& is, InObjectsTable& table) : Terrain(is, table) {}

LavaTerrain::LavaTerrain() : Terrain(LAVA_TERRAIN) {}

LavaTerrain::LavaTerrain(Cell* cell) : Terrain(LAVA_TERRAIN, cell) {};

void LavaTerrain::onAttachUnit(Unit& unit) {
	unit.addEffect(new LavaEffect());
}
