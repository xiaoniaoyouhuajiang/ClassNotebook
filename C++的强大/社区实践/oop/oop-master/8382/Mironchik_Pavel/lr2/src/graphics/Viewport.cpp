#include <GAME/graphics/Viewport.hpp>
#include <cmath>
#include <iostream>


void Viewport::updateViewportSizes() {
	maximumViewportHeight = bottom - top;
	maximumViewportWidth = right - left;

	minScale = std::fmaxf(1.0f, mapWidth / maximumViewportWidth);
	minScale = std::fmaxf(minScale, mapHeight / maximumViewportHeight);
}

void Viewport::validatePosition() {
	viewportLeft += clamp(viewportLeft, left, right - viewportWidth) - viewportLeft;
	viewportTop += clamp(viewportTop, top, bottom - viewportHeight) - viewportTop;
}

float Viewport::clamp(float val, float minVal, float maxVal) const {
	return std::fminf(std::fmaxf(val, minVal), maxVal);
}

sf::Vector2f Viewport::mapCoordsToPixels(const sf::Vector2f& coords) const {
	return sf::Vector2f(
		(coords.x - viewportLeft) * scale,
		(coords.y - viewportTop) * scale
	);
}

sf::Vector2f Viewport::mapPixelsToCoords(const sf::Vector2f& pixels) const {
	return sf::Vector2f(
		pixels.x / scale + viewportLeft,
		pixels.y / scale + viewportTop
	);
}

void Viewport::move(float dx, float dy) {
	viewportLeft += dx;
	viewportTop += dy;
	validatePosition();
}

// this function uses curent scale to compute dx and dy that
// will be applied
void Viewport::moveScaled(float dx, float dy) {
	move(dx / scale, dy / scale);
}

void Viewport::moveTo(float left, float top) {
	viewportLeft = left;
	viewportTop = top;
	validatePosition();
}

void Viewport::setSize(float mapWidth, float mapHeight) {
	setSize(mapWidth, mapHeight, 0, 0, mapWidth, mapHeight);
}

void Viewport::setSize(float mapWidth, float mapHeight, float left, float top, float right, float bottom) {
	this->mapWidth = mapWidth;
	this->mapHeight = mapHeight;
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
	updateViewportSizes();
	setScale(scale);
}

// Just setScale(scale, cx, cy) with current coordinates
void Viewport::setScale(float newScale) {
	scale = clamp(newScale, minScale, maxScale);
	float prevHeight = viewportHeight,
		prevWidth = viewportWidth;
	viewportHeight = mapHeight / scale;
	viewportWidth = mapWidth / scale;
	viewportLeft -= (viewportWidth - prevWidth) / 2;
	viewportTop -= (viewportHeight - prevHeight) / 2;
	validatePosition();
}

float Viewport::getScale() const {
	return scale;
}
/*void Viewport::setScale(float scale, float centerX, float centerY) {
	centerX = clamp(centerX - viewportX - left, 0, viewportWidth);
	centerY = clamp(centerY - viewportY - top, 0, viewportHeight);

	scale = clamp(scale, minScale, maxScale);
	float prevHeight = viewportHeight,
		prevWidth = viewportWidth;
	viewportHeight = mapHeight / scale;
	viewportWidth = mapWidth / scale;

}*/