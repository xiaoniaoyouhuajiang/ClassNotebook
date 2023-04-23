#pragma once

#include <memory>
#include <istream>

#include <SFML/Graphics/Rect.hpp>

#include <GAME/graphics/Viewport.hpp>
#include <GAME/graphics/GridDrawer.hpp>
#include <GAME/serialize/InObjectsTable.hpp>
#include <GAME/serialize/OutObjectsTable.hpp>

using std::istream;
using std::ostream;

class GameBoard;

class BoardView {
private:
	sf::Vector2f _cellSize;
	sf::Rect<float> _boardSize;
	Viewport _viewport;

	GridDrawer _gridDrawer = GridDrawer(&_viewport);

public:
	void readObject(istream& is, InObjectsTable& table);
	void writeObject(ostream& os, OutObjectsTable& table);
	virtual ~BoardView() {}

	BoardView();
	BoardView(const BoardView&);
	BoardView(BoardView&& other);
	BoardView& operator=(const BoardView& other);
	BoardView& operator=(BoardView&& other);

	void update(const sf::Vector2f& screenSize, const sf::Vector2i& cellsCount);

	sf::Vector2f mapCellToCoords(const sf::Vector2i& cell) const;
	sf::Vector2f mapCellToPixels(const sf::Vector2i& cell) const;

	sf::Vector2i mapCoordsToCell(const sf::Vector2f& coords) const;
	sf::Vector2i mapPixelsToCell(const sf::Vector2f& pixels) const;

	const sf::Vector2f& baseCellSize() const;
	sf::Vector2f computeScaledCellSize() const;

	const Viewport& viewport() const;
	const GridDrawer& gridDrawer() const;

	friend class GameBoard;
};