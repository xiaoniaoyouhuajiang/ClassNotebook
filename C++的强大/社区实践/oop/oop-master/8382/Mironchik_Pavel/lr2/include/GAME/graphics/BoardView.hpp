#pragma once

#include <memory>

#include <SFML/Graphics/Rect.hpp>

#include <GAME/graphics/Viewport.hpp>
#include <GAME/graphics/GridDrawer.hpp>

class GameBoard;

class BoardView {
private:
	Viewport _viewport;
	sf::Vector2f _cellSize;
	sf::Rect<float> _boardSize;

	GridDrawer _gridDrawer = GridDrawer(&_viewport);

	void from(const BoardView& other);

public:
	BoardView();
	BoardView(const BoardView&);

	void update(const sf::Vector2f& screenSize, const sf::Vector2i& cellsCount);

	sf::Vector2f mapCellToCoords(const sf::Vector2i& cell) const;
	sf::Vector2f mapCellToPixels(const sf::Vector2i& cell) const;

	sf::Vector2i mapCoordsToCell(const sf::Vector2f& coords) const;
	sf::Vector2i mapPixelsToCell(const sf::Vector2f& pixels) const;

	const sf::Vector2f& baseCellSize() const;
	sf::Vector2f computeScaledCellSize() const;

	const Viewport& viewport() const;
	const GridDrawer& gridDrawer() const;

	BoardView& operator=(const BoardView& other);

	friend class GameBoard;
};