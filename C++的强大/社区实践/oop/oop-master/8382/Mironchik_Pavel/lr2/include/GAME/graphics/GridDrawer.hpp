#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <GAME/graphics/Viewport.hpp>

class GridDrawer : public sf::Drawable {
private:
	Viewport* viewport = nullptr;
	sf::Rect<float> board;
	sf::Vector2i cellsCount;

	float gridWidth;
	sf::Vector2f cellSize;

	const float minGridWidth = 1;
	const float maxGridWidth = 1;

	sf::Color gridColor = sf::Color(243, 243, 243, 100);

	float clamp(float val, float min, float max) const;

	void from(const GridDrawer& other);

public:
	GridDrawer();
	GridDrawer(const GridDrawer& other);
	GridDrawer(Viewport* viewport);

	GridDrawer& operator=(const GridDrawer& other);

	float getGridWidth() const;

	void setViewport(Viewport* viewport);

	void update(const sf::Rect<float>& board, const sf::Vector2i& cellsCount);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const final override;
};