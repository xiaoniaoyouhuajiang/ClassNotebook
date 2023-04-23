#include <GAME/engine/terrains/LavaTerrain.hpp>
#include <GAME/engine/Unit.hpp>
#include <GAME/engine/GameBoard.hpp>
#include <GAME/engine/Cell.hpp>
#include <iostream>

LavaEffect::LavaEffect(): TerrainEffect(LAVA_EFFECT, LAVA_TERRAIN) {}

void LavaEffect::onAttach(Unit& object) {
	TerrainEffect::onAttach(object);
	object.getBoard()->getController().damageUnit(object, _damage);
	std::cout << "onAttach lava" << std::endl;
}

void LavaEffect::onDetach() {
	std::cout << "onDetach lava" << std::endl;
}

void LavaEffect::onOriginMoved(Unit& origin, sf::Vector2i& from, sf::Vector2i& to) {
	TerrainEffect::onOriginMoved(origin, from, to);

	if (isAttached()) {
		_damage *= DAMAGE_MULT;
		origin.getBoard()->getController().damageUnit(origin, _damage);
	}
}

LavaTerrain::LavaTerrain() : Terrain(LAVA_TERRAIN) {}

LavaTerrain::LavaTerrain(Cell* cell) : Terrain(LAVA_TERRAIN, cell) {};

void LavaTerrain::onAttachUnit(Unit& unit) {
	auto ptr = shared_ptr<Effect>(new LavaEffect());
	unit.addEffect(ptr);
}
