#include <GAME/graphics/CellDrawer.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

TextureCellDrawer::TextureCellDrawer() {}

TextureCellDrawer::TextureCellDrawer(const sf::Texture& texture) {
	setTexture(texture);
}

void TextureCellDrawer::setTexture(const sf::Texture& texture) {
	//std::cref<const sf::Texture>(texture);
	rect.setTexture(&texture);
}

void TextureCellDrawer::set(const BoardView& view, const sf::Vector2i& cell) {
	this->cell = cell;
	this->view = &view;
	/*const sf::Vector2u textureSize = sprite.getTexture()->getSize();
	sf::Vector2f scaledSize = view.computeScaledCellSize();
	float scale = std::fminf(scaledSize.x / textureSize.x, scaledSize.y / textureSize.y);
	sprite.setScale(scale, scale);*/
}

void TextureCellDrawer::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	if (view == nullptr)
		return;

	float scale = view->viewport().getScale();
	rect.setSize(view->baseCellSize());
	states.transform.translate(view->mapCellToPixels(cell));
	states.transform.scale(scale, scale);
	target.draw(rect, states);
	auto size = rect.getSize();
}

ColorCellDrawer::ColorCellDrawer() {}

ColorCellDrawer::ColorCellDrawer(const sf::Color& color) {
	setColor(color);
}

void ColorCellDrawer::setColor(const sf::Color& color) {
	rect.setFillColor(color);
}

void ColorCellDrawer::set(const BoardView& view, const sf::Vector2i& cell) {
	rect.setPosition(view.mapCellToPixels(cell));
	rect.setSize(view.computeScaledCellSize());
}

void ColorCellDrawer::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(rect, states);
}