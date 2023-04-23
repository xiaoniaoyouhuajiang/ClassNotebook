#include <SFML/Graphics/RectangleShape.hpp>

#include <GAME/graphics/HealthDrawer.hpp>
#include <GAME/graphics/BoardView.hpp>
#include <GAME/engine/Unit.hpp>
#include <GAME/engine/GameBoard.hpp>

HealthDrawer::HealthDrawer(const Unit& unit) {
	_unit = &unit;
}

void HealthDrawer::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	if (_unit == nullptr || !_unit->isAttached())
		return;

	auto view = _unit->getBoard()->getView();
	auto cellSize = view.computeScaledCellSize();
	auto barSize = sf::Vector2f(cellSize.x * 0.8f, cellSize.y * 0.1f);
	auto lightBarSize = sf::Vector2f(barSize.x * _unit->getHealth() / _unit->getMaxHealth(), barSize.y);
	auto cellCoords = view.mapCellToPixels(_unit->getOccupiedCell());
	auto position = sf::Vector2f(cellCoords.x + (cellSize.x - barSize.x) / 2, cellCoords.y + barSize.y / 2);
	auto paleRect = sf::RectangleShape(barSize);
	auto lightRect = sf::RectangleShape(lightBarSize);

	paleRect.setFillColor(_paleColor);
	lightRect.setFillColor(_lightColor);

	states.transform.translate(position);
	//states.transform.scale(view.viewport().getScale(), view.viewport().getScale());
	target.draw(paleRect, states);
	target.draw(lightRect, states);
}