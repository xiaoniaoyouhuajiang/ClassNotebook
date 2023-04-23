#include <SFML/Graphics/RenderTarget.hpp>

#include <GAME/engine/Terrain.hpp>
#include <GAME/engine/Unit.hpp>
#include <GAME/engine/Cell.hpp>
#include <GAME/engine/GameBoard.hpp>
#include <GAME/utils/Textures.hpp>
#include <GAME/engine/terrains/GroundTerrain.hpp>

Terrain* Terrain::readObject(istream& is, InObjectsTable& table) {
	assert(Serializer::checkControlPoint(is));
	int rawType;
	Serializer::readInt(is, &rawType);
	TerrainType type = static_cast<TerrainType>(rawType);

	if (type == SEA_TERRAIN)
		return new SeaTerrain(is, table);

	if (type == LAVA_TERRAIN)
		return new LavaTerrain(is, table);

	if (type == GROUND_TERRAIN)
		return new GroundTerrain(is, table);

	assert(false);
	return nullptr;
}

void Terrain::writeObject(ostream& os, OutObjectsTable& table, Terrain* terrain) {
	Serializer::writeControlPoint(os);
	int rawType = static_cast<int>(terrain->_type);
	Serializer::writeInt(os, &rawType);
	terrain->writeObject(os, table);
}

Terrain::Terrain(istream& is, InObjectsTable& table) {
	ObjectInfo info;

	int rawType;
	Serializer::readInt(is, &rawType);
	_type = static_cast<TerrainType>(rawType);
	info = table.readInfo(is);
	assert(!info.needWrite);
	table.getObject(info, [this](void* obj) {
		this->_cell = (Cell*)obj;
	});
}

void Terrain::writeObject(ostream& os, OutObjectsTable& table) {
	ObjectInfo info;

	int rawType = static_cast<int>(_type);
	Serializer::writeInt(os, &rawType);
	info = table.writeInfo(os, _cell);
	assert(!info.needWrite);
}

Terrain::Terrain(const Terrain& terrain) {
	*this = terrain;
}

Terrain::Terrain(TerrainType type, Cell* cell) : _type(type), _cell(cell) {}

Terrain::Terrain(TerrainType type) : _type(type) {
}

void Terrain::onAttach(Cell* cell) {
	_cell = cell;
}

void Terrain::onDetach() {
	_cell = nullptr;
}

void Terrain::updateDrawer() const {
	_drawer.set(_cell->board().getView(), _cell->position());
	if (_type == LAVA_TERRAIN)
		_drawer.setTexture(Textures::getInstance().lava());
	else if (_type == SEA_TERRAIN)
		_drawer.setTexture(Textures::getInstance().sea());
	else
		_drawer.setTexture(Textures::getInstance().ground());
}

Terrain& Terrain::operator=(const Terrain& terrain) {
	_type = terrain._type;
	_cell = terrain._cell;
	_drawer = terrain._drawer;

	return *this;
}

TerrainType Terrain::type() const {
	return _type;
}

void Terrain::notifyObjectAtached(GameObject& object) {
	onAttachObject(object);

	Unit* unit = dynamic_cast<Unit*>(&object);

	if (unit != nullptr)
		onAttachUnit(*unit);
}

void Terrain::notifyObjectDetached(GameObject& object) {
	onDetachObject(object);

	Unit* unit = dynamic_cast<Unit*>(&object);

	if (unit != nullptr)
		onDetachUnit(*unit);
}

void Terrain::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	updateDrawer();
	target.draw(_drawer, states);
}