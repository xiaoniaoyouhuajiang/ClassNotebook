#pragma once

#include <SFML/Window/Event.hpp>

class GameBoard;

class Interceptor {
private:
	static const int ATTACHED = 1;
	static const int WAIT_FOR_DETACH = 2;
	static const int DETACHED = 3;

	int attachState = DETACHED;

protected:
	virtual bool onInterceptKey(GameBoard& board, sf::Event::KeyEvent event) = 0;
	virtual bool onInterceptLeftClick(GameBoard& board, const sf::Vector2f& coords) = 0;

	friend class GameBoard;
};