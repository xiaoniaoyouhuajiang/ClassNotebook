#pragma once

#include <SFML/System/Vector2.hpp>

#include <GAME/engine/Attachable.hpp>

class GameBoard;
class GameObject;

class BoardListener {
private:
	static const int WAIT_FOR_DETACH = 1;
	static const int DETACHED = 2;
	static const int ATTACHED = 3;
	static const int WAIT_FOR_ATTACH = 4;

	int _attachState = DETACHED;

	friend class GameBoard;
public:
	virtual void onObjectAttached(GameObject& object) {}
	virtual void onObjectMoved(GameObject& object, sf::Vector2i& from, sf::Vector2i& to) {}
	virtual void onObjectDetached(GameObject& object) {}

	friend class GameBoard;
};