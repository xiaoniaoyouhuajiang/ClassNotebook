#pragma once

#include <memory>
#include <set>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <GAME/engine/GameObject.hpp>
#include <GAME/utils/List.hpp>
#include <GAME/engine/Terrain.hpp>
#include <GAME/engine/terrains/LavaTerrain.hpp>
#include <GAME/engine/terrains/SeaTerrain.hpp>

class Terrain;
class GameObject;

using std::shared_ptr;
using std::set;

class Cell: public sf::Drawable {
private:
	GameBoard& _board;
	set<shared_ptr<GameObject>> _objects;
	shared_ptr<Terrain> _terrain = shared_ptr<Terrain>(new SeaTerrain());
	sf::Vector2i _position;

	void add(shared_ptr<GameObject> object);
	void remove(shared_ptr<GameObject> object);

	friend class GameBoard;
public:
	Cell(GameBoard& board, sf::Vector2i position);

	GameBoard& board();

	const sf::Vector2i& position() const;
	const Terrain& terrain() const;
	void terrain(shared_ptr<Terrain>& terrain);
	const set<shared_ptr<GameObject>>& objects() const;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	~Cell() {
		_objects.clear();
	};
};