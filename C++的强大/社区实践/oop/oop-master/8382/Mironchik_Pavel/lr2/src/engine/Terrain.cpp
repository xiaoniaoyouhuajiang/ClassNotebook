#include <SFML/Graphics/RenderTarget.hpp>

#include <GAME/engine/Terrain.hpp>
#include <GAME/engine/Unit.hpp>
#include <GAME/engine/Cell.hpp>
#include <GAME/engine/GameBoard.hpp>
#include <GAME/utils/Textures.hpp>

Terrain::Terrain(const Terrain& terrain) {
	*this = terrain;
}

Terrain::Terrain(TerrainType type, Cell* cell) : _type(type) {
	updateDrawer();
	onAttach(cell);
}

Terrain::Terrain(TerrainType type) : _type(type) {
	updateDrawer();
}

void Terrain::updateDrawer() {
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

void Terrain::onAttach(Cell* cell) {
	_cell = cell;
	_drawer.set(cell->board().getView(), cell->position());
}

void Terrain::onDetach() {
	_cell = nullptr;
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
	target.draw(_drawer, states);
}