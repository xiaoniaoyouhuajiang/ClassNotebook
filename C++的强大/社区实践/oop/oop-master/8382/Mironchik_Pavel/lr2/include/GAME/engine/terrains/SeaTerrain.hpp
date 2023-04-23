#pragma once

#include <cmath>

#include <GAME/engine/Terrain.hpp>
#include <GAME/engine/terrains/TerrainEffect.hpp>

class SeaEffect : public TerrainEffect {
public:
	SeaEffect();

	virtual float transformAttackRange(float range) const override;

	virtual float transformSpeed(float speed) const override;
};

class SeaTerrain : public Terrain {
public:
	SeaTerrain();
	SeaTerrain(Cell* cell);

	virtual void onAttachUnit(Unit& unit) override;
};