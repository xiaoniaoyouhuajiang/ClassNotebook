#pragma once

#include <memory>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <GAME/graphics/BoardView.hpp>

class BoardView;

class CellDrawer : public sf::Drawable {
public:
	virtual void set(const BoardView& view, const sf::Vector2i& cell) = 0;
};

class TextureCellDrawer : public CellDrawer {
private:
	mutable sf::RectangleShape rect;
	const BoardView* view;
	sf::Vector2i cell;

public:
	TextureCellDrawer();
	TextureCellDrawer(const sf::Texture& texture);

	void setTexture(const sf::Texture& texture);

	void set(const BoardView& view, const sf::Vector2i& cell) override;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

class ColorCellDrawer : public CellDrawer {
private:
	sf::RectangleShape rect;

public:
	ColorCellDrawer();
	ColorCellDrawer(const sf::Color& color);

	void setColor(const sf::Color& color);

	void set(const BoardView& view, const sf::Vector2i& cell) override;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};