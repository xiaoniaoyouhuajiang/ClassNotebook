#pragma once

#include <memory>
#include <iostream>

#include <SFML/Graphics/Drawable.hpp>

#include <GAME/graphics/CellDrawer.hpp>
#include <GAME/serialize/Serializer.hpp>
#include <GAME/serialize/InObjectsTable.hpp>
#include <GAME/serialize/OutObjectsTable.hpp>

using std::shared_ptr;
using std::istream;
using std::ostream;

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
	mutable TextureCellDrawer _drawer;
	TerrainType _type;
	Cell* _cell;

	void onAttach(Cell* cell);
	void onDetach();

	void updateDrawer() const;

	void notifyObjectAtached(GameObject& object);
	void notifyObjectDetached(GameObject& object);

	friend class Cell;

protected:
	Terrain(TerrainType type);
	Terrain(TerrainType type, Cell* cell);

	virtual void writeObject(ostream& os, OutObjectsTable& table);

public:
	Terrain(istream& is, InObjectsTable& table);
	static Terrain* readObject(istream& is, InObjectsTable& table);
	static void writeObject(ostream& is, OutObjectsTable& table, Terrain* terrain);
	virtual ~Terrain() {}

	Terrain(const Terrain& terrain);

	Terrain& operator=(const Terrain& terrain);

	TerrainType type() const;

	virtual void onAttachObject(GameObject& object) {}
	virtual void onDetachObject(GameObject& object) {}

	virtual void onAttachUnit(Unit& unit) {}
	virtual void onDetachUnit(Unit& unit) {}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};