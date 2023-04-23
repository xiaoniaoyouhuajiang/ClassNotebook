#pragma once

#include <list>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <GAME/utils/VectorsSet.hpp>
#include <GAME/graphics/CellDrawer.hpp>

using std::list;

class GameBoard;

class ShapePoint {
public:

	sf::Vector2i coords;
	bool hasLeft = false, hasTop = false, hasRight = false, hasBottom = false;

	ShapePoint(const sf::Vector2i& coords) {
		this->coords = coords;
	}
};

class ShapeDrawer : public sf::Drawable {
private:
	const GameBoard* _board = nullptr;
	list<ShapePoint> _points;
	sf::Color _backgroundColor = sf::Color(80, 161, 248, 50);
	sf::Color _borderColor = sf::Color(242, 167, 3, 255);

public:
	void setBoard(const GameBoard* board);
	void setPoints(const VectorsSet<int> points);

	void setBackgroundColor(const sf::Color& color);
	void setBorderColor(const sf::Color& color);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void drawBackground(sf::RenderTarget& target, sf::RenderStates states, const sf::Vector2i& point) const;
	void drawHorizontalLine(sf::RenderTarget& target, sf::RenderStates states, const sf::Vector2i& start) const;
	void drawVerticalLine(sf::RenderTarget& target, sf::RenderStates states, const sf::Vector2i& start) const;
};