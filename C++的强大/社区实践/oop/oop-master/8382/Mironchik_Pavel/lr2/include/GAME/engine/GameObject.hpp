#pragma once

#include <memory>
#include <set>

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>

#include <GAME/engine/RelativePositioned.hpp>
#include <GAME/engine/RelativeSized.hpp>
#include <GAME/engine/Focusable.hpp>
#include <GAME/utils/List.hpp>
#include <GAME/engine/Tangible.hpp>
#include <GAME/engine/BoardListener.hpp>

class GameBoard;

class GameObject: public Focusable, public Tangible, public BoardListener {
private:
	static int CUR_ID;

	int _id = CUR_ID++;
	GameBoard *board = nullptr;
	mutable sf::Vector2i occupiedCell = sf::Vector2i(0, 0);
	int attachState = DETACHED;

	void attach(GameBoard *board);
	void detach();

	static const int WAIT_FOR_ATTACH = 1;
	static const int ATTACHED = 2;
	static const int WAIT_FOR_DETACH = 3;
	static const int DETACHED = 4;

public:

	GameObject();
	GameObject(const GameObject& from);

	int id() const;

	bool isAttached() const;

	GameBoard* getBoard() const;

	sf::Vector2i& getOccupiedCell() const;
	void setOccupiedCell(sf::Vector2i cell);

	virtual int info() const = 0;

	virtual void onMapChanged() {};
	
	virtual void onFrameStart() {}
	virtual bool onClick(sf::Vector2i& cell);
	virtual bool onKeyPressed(sf::Event key);
	virtual void onFrame(long msPassed) {}
	// here you can initialize variables that you need for drawing.
	virtual void onPreDraw() {};
	virtual void onDraw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
	virtual void onFrameEnd() {}

	virtual void onAttach() {}
	virtual void onDetach() {}

	virtual GameObject* copy() = 0;

	friend class GameBoard;
};

