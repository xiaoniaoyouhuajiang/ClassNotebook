#pragma once

#include <cmath>
#include <iostream>

#include <GAME/engine/Terrain.hpp>
#include <GAME/engine/terrains/TerrainEffect.hpp>
#include <GAME/serialize/Serializer.hpp>
#include <GAME/serialize/InObjectsTable.hpp>
#include <GAME/serialize/OutObjectsTable.hpp>

using std::istream;
using std::ostream;

class SeaEffect : public TerrainEffect {
public:
	SeaEffect(istream& is, InObjectsTable& table);
	SeaEffect();

	virtual float transformAttackRange(float range) const override;

	virtual float transformSpeed(float speed) const override;
};

class SeaTerrain : public Terrain {
public:
	SeaTerrain(istream& is, InObjectsTable& table);

	SeaTerrain();
	SeaTerrain(Cell* cell);

	virtual void onAttachUnit(Unit& unit) override;
};