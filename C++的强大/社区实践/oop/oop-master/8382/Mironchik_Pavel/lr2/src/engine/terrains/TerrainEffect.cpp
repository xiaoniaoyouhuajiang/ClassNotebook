#include <GAME/engine/terrains/TerrainEffect.hpp>
#include <GAME/engine/Unit.hpp>
#include <GAME/engine/GameBoard.hpp>

TerrainEffect::TerrainEffect(EffectName name, TerrainType type):
	Effect(name), _terrainType(type)
{}

void TerrainEffect::onOriginMoved(Unit& origin, sf::Vector2i& from, sf::Vector2i& to) {
	if (origin.getBoard()->getCell(to).terrain().type() == _terrainType)
		return;

	origin.removeEffect(name());
}

void TerrainEffect::onOriginDetached(Unit& origin) {
	origin.removeEffect(name());
}