#pragma once

#include <GAME/graphics/Viewport.hpp>

#include <SFML/Window/Event.hpp>

class GameBoard;

enum MouseTrackerState {
	IDLE,
	PRESSED,
	MOVE
};

class MouseTrackerListener {
public:
	virtual void onClickLeft(sf::Vector2f& coords, bool wasMoved) {}
	virtual void onMove(float dx, float dy) {}
};

class MouseTracker {
private:
	MouseTrackerState leftTrackState = IDLE;
	sf::Vector2f start = sf::Vector2f(0.0f, 0.0f);
	sf::Vector2f last = start;
	MouseTrackerListener* listener;
	const Viewport *viewport;


	void onDown(sf::Event& event);
	void onMove(sf::Event& event);
	void onUp(sf::Event& event);

public:
	MouseTracker(istream& is, InObjectsTable& table);
	void writeObject(ostream& os, OutObjectsTable& table);
	virtual ~MouseTracker() {}

	MouseTracker(
		MouseTrackerListener *listener = nullptr,
		const Viewport* viewport = nullptr
	) : listener(listener), 
		viewport(viewport)
	{};

	bool isLeftPressed();

	bool processEvent(sf::Event& event);

	void setListener(MouseTrackerListener* listener);
	void setViewport(const Viewport*);

	const sf::Vector2f& getStartPixels() const;
	const sf::Vector2f& getLastPixels() const;

	sf::Vector2f computeStartCoords() const;
	sf::Vector2f computeLastCoords() const;
};