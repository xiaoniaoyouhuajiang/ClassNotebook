#pragma once

#include <memory>

#include <SFML/Graphics/Drawable.hpp>

#include <GAME/graphics/CellDrawer.hpp>

using std::shared_ptr;

class GameObject;
class Cell;
class Unit;

enum TerrainType {
	SEA_TERRAIN,
	LAVA_TERRAIN,
	GROUND_TERRAIN
};

class Terrain: public sf::Drawable {
private:
	TextureCellDrawer _drawer;
	TerrainType _type;
	Cell* _cell;

	void updateDrawer();

	void onAttach(Cell* cell);
	void onDetach();

	void notifyObjectAtached(GameObject& object);
	void notifyObjectDetached(GameObject& object);

	friend class Cell;

protected:
	Terrain(TerrainType type);
	Terrain(TerrainType type, Cell* cell);

public:
	Terrain(const Terrain& terrain);

	Terrain& operator=(const Terrain& terrain);

	TerrainType type() const;

	virtual void onAttachObject(GameObject& object) {}
	virtual void onDetachObject(GameObject& object) {}

	virtual void onAttachUnit(Unit& unit) {}
	virtual void onDetachUnit(Unit& unit) {}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};