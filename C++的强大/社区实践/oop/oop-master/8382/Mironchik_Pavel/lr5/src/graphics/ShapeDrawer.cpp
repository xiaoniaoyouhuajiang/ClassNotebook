#include <GAME/graphics/ShapeDrawer.hpp>
#include <GAME/engine/GameBoard.hpp>
#include <GAME/graphics/BoardView.hpp>

ShapeDrawer::ShapeDrawer(istream& is, InObjectsTable& table) {
	ObjectInfo info;

	info = table.readInfo(is);
	assert(!info.needWrite);
	table.getObject(info, [this](void* obj) {
		this->_board = (GameBoard*)obj;
	});

	int count;
	Serializer::readInt(is, &count);
	for (int i = 0; i < count; i++) {
		ShapePoint point;
		Serializer::read(is, &point, sizeof(ShapePoint));
		_points.push_back(point);
	}

	Serializer::read(is, &_backgroundColor, sizeof(sf::Color));
	Serializer::read(is, &_borderColor, sizeof(sf::Color));
}

void ShapeDrawer::writeObject(ostream& os, OutObjectsTable& table) {
	ObjectInfo info;

	info = table.writeInfo(os, _board);
	assert(!info.needWrite);

	int count = _points.size();
	Serializer::writeInt(os, &count);
	for (ShapePoint& point : _points) {
		Serializer::write(os, &point, sizeof(ShapePoint));
	}

	Serializer::write(os, &_backgroundColor, sizeof(sf::Color));
	Serializer::write(os, &_borderColor, sizeof(sf::Color));
}

void ShapeDrawer::setBoard(const GameBoard* board) {
	_board = board;
}
void ShapeDrawer::setPoints(const VectorsSet<int> points) {
	_points.clear();
	for (auto& point : points) {
		ShapePoint sp = ShapePoint(point);
		sp.hasLeft = points.count(point - sf::Vector2i(1, 0));
		sp.hasTop = points.count(point - sf::Vector2i(0, 1));
		sp.hasRight = points.count(point + sf::Vector2i(1, 0));
		sp.hasBottom = points.count(point + sf::Vector2i(0, 1));
		_points.push_back(sp);
	}
}

void ShapeDrawer::setBackgroundColor(const sf::Color& color) {
	_backgroundColor = color;
}

void ShapeDrawer::setBorderColor(const sf::Color& color) {
	_borderColor = color;
}

void ShapeDrawer::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (auto point : _points) {
		drawBackground(target, states, point.coords);

		if (!point.hasLeft)
			drawVerticalLine(target, states, point.coords);

		if (!point.hasTop)
			drawHorizontalLine(target, states, point.coords);

		if (!point.hasRight)
			drawVerticalLine(target, states, point.coords + sf::Vector2i(1, 0));

		if (!point.hasBottom)
			drawHorizontalLine(target, states, point.coords + sf::Vector2i(0, 1));
	}
}

void ShapeDrawer::drawBackground(sf::RenderTarget& target, sf::RenderStates states, const sf::Vector2i& point) const {
	sf::RectangleShape rect(_board->getView().baseCellSize());
	rect.setFillColor(_backgroundColor);
	float scale = _board->getView().viewport().getScale();
	states.transform.translate(_board->getView().mapCellToPixels(point));
	states.transform.scale(scale, scale);
	target.draw(rect, states);
}

void ShapeDrawer::drawHorizontalLine(sf::RenderTarget& target, sf::RenderStates states, const sf::Vector2i& start) const {
	float lineWidth = _board->getView().gridDrawer().getGridWidth();
	float lineLength = _board->getView().baseCellSize().x + lineWidth;
	sf::RectangleShape line(sf::Vector2f(lineLength, lineWidth));
	line.setFillColor(_borderColor);
	float scale = _board->getView().viewport().getScale();
	states.transform.translate(_board->getView().mapCellToPixels(start));
	states.transform.scale(scale, scale);
	states.transform.translate(-lineWidth / 2, -lineWidth / 2);
	target.draw(line, states);
}

void ShapeDrawer::drawVerticalLine(sf::RenderTarget& target, sf::RenderStates states, const sf::Vector2i& start) const {
	float lineWidth = _board->getView().gridDrawer().getGridWidth();
	float lineLength = _board->getView().baseCellSize().y + lineWidth;
	sf::RectangleShape line(sf::Vector2f(lineWidth, lineLength));
	line.setFillColor(_borderColor);
	float scale = _board->getView().viewport().getScale();
	states.transform.translate(_board->getView().mapCellToPixels(start));
	states.transform.scale(scale, scale);
	states.transform.translate(-lineWidth / 2, -lineWidth / 2);
	target.draw(line, states);
}