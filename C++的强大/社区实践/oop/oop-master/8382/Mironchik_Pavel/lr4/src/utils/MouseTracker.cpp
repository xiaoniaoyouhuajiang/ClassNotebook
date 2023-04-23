#include <iostream>

#include <GAME/utils/MouseTracker.hpp>
#include <GAME/log/Log.hpp>

void MouseTracker::setListener(MouseTrackerListener* listener) {
	this->listener = listener;
}

void MouseTracker::setViewport(const Viewport* viewport) {
	this->viewport = viewport;
}

bool MouseTracker::isLeftPressed() {
	return leftTrackState != IDLE;
}

bool MouseTracker::processEvent(sf::Event& event) {
	if (event.type == sf::Event::MouseButtonPressed) {
		if (event.mouseButton.button == sf::Mouse::Right)
			return false;

		onDown(event);
		return true;
	}

	if (event.type == sf::Event::MouseButtonReleased) {
		if (event.mouseButton.button == sf::Mouse::Right)
			return false;

		onUp(event);
		return true;
	}

	if (event.type == sf::Event::MouseMoved) {
		onMove(event);
		return true;
	}

	return false;
}

void MouseTracker::onDown(sf::Event& event) {
	if (leftTrackState != IDLE)
		return;

	start = sf::Vector2f((float) event.mouseButton.x, (float) event.mouseButton.y);
	last = start;
	leftTrackState = PRESSED;

	LogInfo info;
	info.name = "MouseTracker:onDown";
	info.pushParam("x", std::to_string(start.x));
	info.pushParam("y", std::to_string(start.y));
	Log::log(info);
}

void MouseTracker::onMove(sf::Event& event) {
	auto prev = last;
	last = sf::Vector2f((float) event.mouseMove.x, (float) event.mouseMove.y);

	if (leftTrackState != IDLE)
		leftTrackState = MOVE;

	if (listener != nullptr)
		listener->onMove(
			(last.x - prev.x) / viewport->getScale(), 
			(last.y - prev.y) / viewport->getScale()
		);
}

void MouseTracker::onUp(sf::Event& event) {
	last = sf::Vector2f((float) event.mouseButton.x, (float) event.mouseButton.y);
	sf::Vector2f lastCoords = computeLastCoords();

	if (listener != nullptr)
		listener->onClickLeft(lastCoords, leftTrackState == MOVE);

	leftTrackState = IDLE;

	LogInfo info;
	info.name = "MouseTracker:onUp";
	info.pushParam("x", std::to_string(start.x));
	info.pushParam("y", std::to_string(start.y));
	Log::log(info);
}

const sf::Vector2f& MouseTracker::getStartPixels() const {
	return start;
}

const sf::Vector2f& MouseTracker::getLastPixels() const {
	return last;
}

sf::Vector2f MouseTracker::computeStartCoords() const {
	return viewport->mapPixelsToCoords(start);
}

sf::Vector2f MouseTracker::computeLastCoords() const {
	return viewport->mapPixelsToCoords(last);
}