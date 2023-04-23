#include <GAME/engine/RelativePositioned.hpp>

void RelativePositioned::setRelativeX(float cellX) {
	relativePosition.x = cellX;
}

void RelativePositioned::setRelativeY(float cellY) {
	relativePosition.y = cellY;
}

float RelativePositioned::getRelativeX() {
	return relativePosition.x;
}

float RelativePositioned::getRelativeY() {
	return relativePosition.y;
}

void RelativePositioned::setRelativePosition(sf::Vector2f& position) {
	relativePosition = position;
}

sf::Vector2f& RelativePositioned::getRelativePosition() {
	return relativePosition;
}

void RelativePositioned::offsetRelativeX(float dx) {
	relativePosition.x += dx;
}

void RelativePositioned::offsetRelativeY(float dy) {
	relativePosition.y += dy;
}