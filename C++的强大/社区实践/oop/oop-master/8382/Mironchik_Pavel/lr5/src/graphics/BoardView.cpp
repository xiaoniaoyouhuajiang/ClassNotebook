#include <memory>

#include <GAME/graphics/BoardView.hpp>
#include <GAME/serialize/Serializer.hpp>

void BoardView::readObject(istream& is, InObjectsTable& table) {
	ObjectInfo info;

	info = table.readInfo(is);
	if (info.needWrite) {
		_viewport = Viewport(is, table);
		table.setObject(info, &_viewport);
	}
	else {
		table.getObject(info, [this](void* object) {
			this->_viewport = *((Viewport*)object);
		});
	}

	Serializer::read(is, (void*)&_cellSize, sizeof(sf::Vector2f));
	Serializer::read(is, (void*)&_boardSize, sizeof(sf::Rect<float>));
	_gridDrawer.readObject(is, table);
}

void BoardView::writeObject(ostream& os, OutObjectsTable& table) {
	ObjectInfo info;

	info = table.writeInfo(os, &_viewport);
	if (info.needWrite)
		_viewport.writeObject(os, table);

	Serializer::write(os, (void*)&_cellSize, sizeof(sf::Vector2f));
	Serializer::write(os, (void*)&_boardSize, sizeof(sf::Rect<float>));
	_gridDrawer.writeObject(os, table);
}

BoardView::BoardView() {
}

BoardView::BoardView(const BoardView& view) {
	_viewport = view._viewport;
	_cellSize = view._cellSize;
	_boardSize = view._boardSize;
}

BoardView::BoardView(BoardView&& other) {
	*this = other;
}

BoardView& BoardView::operator=(const BoardView& other) {
	if (this == &other)
		return *this;

	*this = BoardView(other);
	return *this;
}

BoardView& BoardView::operator=(BoardView&& other) {
	if (this == &other)
		return *this;

	_viewport = std::move(other._viewport);
	_cellSize = std::move(other._cellSize);
	_boardSize = std::move(other._boardSize);
	return *this;
}

void BoardView::update(const sf::Vector2f& screenSize, const sf::Vector2i& cellsCount) {
	float side = fminf(screenSize.x / cellsCount.x, screenSize.y / cellsCount.y);
	_cellSize = sf::Vector2f(side, side);
	float boardWidth = _cellSize.x * cellsCount.x,
		boardHeight = _cellSize.y * cellsCount.y;
	sf::Vector2f center(screenSize.x / 2, screenSize.y / 2);

	_boardSize = sf::Rect<float>(
		(float)(screenSize.x - boardWidth) / 2,
		(float)(screenSize.y - boardHeight) / 2,
		boardWidth,
		boardHeight
		);

	_viewport.setSize(
		screenSize.x,
		screenSize.y,
		_boardSize.left - 100,
		_boardSize.top - 100,
		_boardSize.left + _boardSize.width + 100,
		_boardSize.top + _boardSize.height + 100
	);

	_gridDrawer.update(_boardSize, cellsCount);
}

sf::Vector2f BoardView::mapCellToCoords(const sf::Vector2i& cell) const {
	return sf::Vector2f(
		cell.x * _cellSize.x + _boardSize.left,
		cell.y * _cellSize.y + _boardSize.top
	);
}

sf::Vector2f BoardView::mapCellToPixels(const sf::Vector2i& cell) const {
	return _viewport.mapCoordsToPixels(mapCellToCoords(cell));
}

sf::Vector2i BoardView::mapCoordsToCell(const sf::Vector2f& coords) const {
	return sf::Vector2i(
		std::floorl((coords.x - _boardSize.left) / _cellSize.x),
		std::floorl((coords.y - _boardSize.top) / _cellSize.y)
	);
}

sf::Vector2i BoardView::mapPixelsToCell(const sf::Vector2f& pixels) const {
	return mapCoordsToCell(_viewport.mapPixelsToCoords(pixels));
}

const sf::Vector2f& BoardView::baseCellSize() const {
	return _cellSize;
}

sf::Vector2f BoardView::computeScaledCellSize() const {
	return sf::Vector2f(
		_cellSize.x * _viewport.getScale(),
		_cellSize.y * _viewport.getScale()
	);
}

const Viewport& BoardView::viewport() const {
	return _viewport;
}

const GridDrawer& BoardView::gridDrawer() const {
	return _gridDrawer;
}