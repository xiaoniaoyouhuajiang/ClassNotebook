#include <GAME/graphics/BoardView.hpp>

BoardView::BoardView() {
}

BoardView::BoardView(const BoardView& view) {
	_viewport = view._viewport;
	_cellSize = view._cellSize;
	_boardSize = view._boardSize;
}

BoardView& BoardView::operator=(const BoardView& other) {
	from(other);
	return *this;
}

void BoardView::from(const BoardView& other) {
	this->_viewport = other._viewport;
	this->_boardSize = other._boardSize;
	this->_cellSize = other._cellSize;
	this->_gridDrawer = other._gridDrawer;
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