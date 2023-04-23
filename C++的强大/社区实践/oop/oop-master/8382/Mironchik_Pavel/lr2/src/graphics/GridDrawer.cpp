#include <cmath>

#include <SFML/Graphics/RectangleShape.hpp>

#include <GAME/graphics/GridDrawer.hpp>

GridDrawer::GridDrawer() {}

GridDrawer::GridDrawer(const GridDrawer& other) {
	from(other);
}

GridDrawer::GridDrawer(Viewport* viewport) { 
	setViewport(viewport);
}

GridDrawer& GridDrawer::operator=(const GridDrawer& other) {
	from(other);
	return *this;
}

float GridDrawer::getGridWidth() const {
	return gridWidth;
}

void GridDrawer::from(const GridDrawer& other) {
	this->viewport = other.viewport;
	this->board = other.board;
	this->cellsCount = other.cellsCount;
	this->gridWidth = other.gridWidth;
	this->cellSize = other.cellSize;
	this->gridColor = other.gridColor;
}

float GridDrawer::clamp(float val, float min, float max) const {
	return std::min(std::max(val, min), max);
}

void GridDrawer::setViewport(Viewport* viewport) {
	this->viewport = viewport;
}

void GridDrawer::update(const sf::Rect<float>& board, const sf::Vector2i& cellsCount) {
	this->board = board;
	this->cellsCount = cellsCount;

	cellSize = sf::Vector2f(board.width / cellsCount.x, board.height / cellsCount.y);
	gridWidth = clamp(std::fminf(cellSize.x, cellSize.y) / 10, minGridWidth, maxGridWidth);
}

void GridDrawer::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	float scaledGridWidth = gridWidth; //clamp(gridWidth * viewport->getScale(), minGridWidth, maxGridWidth);
	sf::RectangleShape rect(sf::Vector2f(scaledGridWidth, board.height * viewport->getScale()));
	sf::Vector2f coordsStartPosition = sf::Vector2f(board.left, board.top);//sf::Vector2f(board.left - gridWidth / 2, board.top - gridWidth / 2);
	sf::Vector2f pixelsPosition = viewport->mapCoordsToPixels(coordsStartPosition);
	pixelsPosition.x -= gridWidth / 2;
	pixelsPosition.y -= gridWidth / 2;
	rect.setPosition(pixelsPosition);
	rect.setFillColor(gridColor);
	sf::Vector2f offset(cellSize.x * viewport->getScale(), cellSize.y * viewport->getScale());

	for (int i = 0; i <= cellsCount.x; i++) {
		target.draw(rect);
		pixelsPosition.x += offset.x;
		rect.setPosition(pixelsPosition);
	}

	pixelsPosition = viewport->mapCoordsToPixels(coordsStartPosition);
	rect.setPosition(pixelsPosition);
	rect.setSize(sf::Vector2f(board.width * viewport->getScale(), scaledGridWidth));

	for (int i = 0; i <= cellsCount.y; i++) {
		target.draw(rect);
		pixelsPosition.y += offset.y;
		rect.setPosition(pixelsPosition);
	}
}