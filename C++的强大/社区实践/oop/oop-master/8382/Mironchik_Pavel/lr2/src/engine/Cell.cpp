#include <GAME/engine/Cell.hpp>

Cell::Cell(GameBoard& board, sf::Vector2i position): 
	_board(board), 
	_position(position) 
{
	_terrain->onAttach(this);
}

GameBoard& Cell::board() {
	return _board;
}

const sf::Vector2i& Cell::position() const {
	return _position;
}

const set<shared_ptr<GameObject>>& Cell::objects() const {
	return _objects;
}

const Terrain& Cell::terrain() const {
	return *_terrain;
}

void Cell::terrain(shared_ptr<Terrain>& terrain) {
	_terrain->onDetach();
	_terrain = shared_ptr<Terrain>(terrain);
	_terrain->onAttach(this);
}

void Cell::add(shared_ptr<GameObject> object) {
	_objects.insert(object);

	if (_terrain != nullptr)
		_terrain->notifyObjectAtached(*object);
}

void Cell::remove(shared_ptr<GameObject> object) {
	if (_terrain != nullptr)
		_terrain->notifyObjectDetached(*object);

	_objects.erase(object);
}

void Cell::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	if (_terrain != nullptr)
		target.draw(*_terrain, states);
}