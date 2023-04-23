#include <GAME/engine/Cell.hpp>

Cell::Cell(istream& is, InObjectsTable& table, GameBoard& board) : _board(board) {
	ObjectInfo info;

	Serializer::read(is, &_position, sizeof(sf::Vector2i));

	if (_position.x == 0 && _position.y == 0) {
		Log::log(string("ff"));
	}

	LogInfo logInfo;
	logInfo.name = "Cell:readObject";
	logInfo.pushParam("x", std::to_string(_position.x));
	logInfo.pushParam("y", std::to_string(_position.y));
	Log::log(logInfo);

	assert(Serializer::checkControlPoint(is));
	int childCount;
	Serializer::readInt(is, &childCount);
	for (int i = 0; i < childCount; i++) {
		info = table.readInfo(is);
		assert(!info.needWrite);
		table.getObject(info, [this](void* obj) {
			this->_objects.insert((GameObject*)obj);
		});
	}

	info = table.readInfo(is);
	if (info.needWrite)
		table.setObject(info, Terrain::readObject(is, table));
	table.getObject(info, [this](void* obj) {
		this->_terrain = shared_ptr<Terrain>((Terrain*) obj);
	});

	assert(Serializer::checkControlPoint(is, 389483));
}

void Cell::writeObject(ostream& os, OutObjectsTable& table) {
	ObjectInfo info;

	Serializer::write(os, &_position, sizeof(sf::Vector2i));

	Serializer::writeControlPoint(os);
	int childCount = _objects.size();
	Serializer::writeInt(os, &childCount);
	for (GameObject* obj : _objects) {
		info = table.writeInfo(os, obj);
		if (info.needWrite)
			GameObject::writeObject(os, table, obj);
	}

	info = table.writeInfo(os, &_terrain);
	if (info.needWrite)
		Terrain::writeObject(os, table, _terrain.get());

	Serializer::writeControlPoint(os, 389483);
}

Cell::Cell(const Cell& other) : _board(other._board) {
	_objects = other._objects;
	_terrain = other._terrain;
	_position = other._position;
}

Cell::Cell(GameBoard& board, sf::Vector2i position): 
	_board(board), 
	_position(position) 
{
	_terrain->onAttach(this);
}

Cell& Cell::operator=(Cell&& other) {
	if (this == &other)
		return *this;

	assert(&_board == &other._board);
	_objects = std::move(other._objects);
	_terrain = std::move(other._terrain);
	_position = std::move(other._position);
	return *this;
}

GameBoard& Cell::board() {
	return _board;
}

const sf::Vector2i& Cell::position() const {
	return _position;
}

const set<GameObject*>& Cell::objects() const {
	return _objects;
}

const Terrain& Cell::terrain() const {
	return *_terrain;
}

void Cell::terrain(shared_ptr<Terrain> terrain) {
	_terrain->onDetach();
	_terrain = shared_ptr<Terrain>(terrain);
	_terrain->onAttach(this);
}

void Cell::add(GameObject* object) {
	_objects.insert(object);

	if (_terrain != nullptr)
		_terrain->notifyObjectAtached(*object);
}

void Cell::remove(GameObject* object) {
	if (_terrain != nullptr)
		_terrain->notifyObjectDetached(*object);

	_objects.erase(object);
}

void Cell::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	if (_terrain != nullptr)
		target.draw(*_terrain, states);
}