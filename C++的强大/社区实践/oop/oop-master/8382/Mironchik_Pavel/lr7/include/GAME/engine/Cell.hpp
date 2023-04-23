#pragma once

#include <memory>
#include <set>
#include <iostream>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <GAME/engine/GameObject.hpp>
#include <GAME/utils/List.hpp>
#include <GAME/engine/Terrain.hpp>
#include <GAME/engine/terrains/LavaTerrain.hpp>
#include <GAME/engine/terrains/SeaTerrain.hpp>
#include <GAME/serialize/Serializer.hpp>
#include <GAME/serialize/InObjectsTable.hpp>
#include <GAME/serialize/OutObjectsTable.hpp>

class Terrain;
class GameObject;

using std::shared_ptr;
using std::set;
using std::istream;
using std::ostream;

class Cell: public sf::Drawable {
private:
	GameBoard& _board;
	set<GameObject*> _objects;
	shared_ptr<Terrain> _terrain = shared_ptr<Terrain>(new SeaTerrain());
	sf::Vector2i _position;

	void add(GameObject* object);
	void remove(GameObject* object);

	friend class GameBoard;

public:
	Cell(istream& is, InObjectsTable& table, GameBoard& board);
	void writeObject(ostream& os, OutObjectsTable& table);
	virtual ~Cell() {
		_objects.clear();
	};

	Cell& operator=(Cell&& other);

	Cell(const Cell& other);
	Cell(GameBoard& board, sf::Vector2i position);
	GameBoard& board();

	const sf::Vector2i& position() const;
	const Terrain& terrain() const;
	void terrain(shared_ptr<Terrain> terrain);
	const set<GameObject*>& objects() const;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};