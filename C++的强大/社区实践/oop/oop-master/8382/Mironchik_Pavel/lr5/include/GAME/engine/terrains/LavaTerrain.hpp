#pragma once

#include <GAME/engine/terrains/TerrainEffect.hpp>
#include <GAME/engine/Terrain.hpp>

class LavaEffect : public TerrainEffect {
private:
	const float DAMAGE = 1.0f;
	const float DAMAGE_MULT = 1.2f;

	float _damage = DAMAGE;

protected:
	virtual void writeObject(ostream& os, OutObjectsTable& table) override;

public:
	LavaEffect(istream& is, InObjectsTable& table);
	LavaEffect();

	virtual void onAttach(Unit& object) override;
	virtual void onDetach() override;
	virtual void onOriginMoved(Unit& origin, sf::Vector2i& from, sf::Vector2i& to);
};

class LavaTerrain : public Terrain {
public:
	LavaTerrain(istream& is, InObjectsTable& table);

	LavaTerrain();
	LavaTerrain(Cell* cell);

	virtual void onAttachUnit(Unit& unit) override;
};