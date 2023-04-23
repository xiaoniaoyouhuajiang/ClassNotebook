#pragma once

#include <GAME/engine/Unit.hpp>
#include <GAME/engine/Effect.hpp>
#include <GAME/engine/Terrain.hpp>

class Unit;

class TerrainEffect : public Effect {
private:
	TerrainType _terrainType;
public:
	TerrainEffect(EffectName name, TerrainType type);

	virtual void onOriginMoved(Unit& origin, sf::Vector2i& from, sf::Vector2i& to) override;
	virtual void onOriginDetached(Unit& origin) override;
};