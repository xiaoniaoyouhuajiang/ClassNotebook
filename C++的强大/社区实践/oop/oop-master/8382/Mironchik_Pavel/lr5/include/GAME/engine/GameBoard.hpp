#pragma once

#include <GAME/engine/GameObject.hpp>
#include <GAME/graphics/Viewport.hpp>
#include <GAME/utils/List.hpp>
#include <GAME/utils/MouseTracker.hpp>
#include <GAME/engine/Cell.hpp>
#include <GAME/engine/GameController.hpp>
#include <GAME/graphics/BoardView.hpp>
#include <GAME/graphics/GridDrawer.hpp>
#include <GAME/engine/Interceptor.hpp>
#include <GAME/utils/SharedSet.h>
#include <GAME/engine/BoardListener.hpp>
#include <GAME/serialize/InObjectsTable.hpp>
#include <GAME/serialize/OutObjectsTable.hpp>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Rect.hpp>

#include <ctime>
#include <cmath>
#include <string>
#include <memory>
#include <set>


using std::shared_ptr;
using std::set;

class GameObject;
class GameBoardSerializer;

class GameBoard: public sf::Drawable, public MouseTrackerListener {
private:
	BoardView view;
	List<shared_ptr<GameObject>> children = List<shared_ptr<GameObject>>();
	MouseTracker _mouseTracker = MouseTracker(this, &view.viewport());
	sf::Vector2i cellsCount;
	Cell*** cells;
	mutable Cell* trashCell = new Cell(*this, sf::Vector2i(-1, -1));
	GameController controller;
	List<BoardListener*> _listeners;
	List<shared_ptr<Interceptor>> interceptors;

	void notifyObjectAttached(shared_ptr<GameObject> object);
	void notifyObjectMoved(shared_ptr<GameObject> object, sf::Vector2i& from, sf::Vector2i& to);
	void notifyObjectDetached(shared_ptr<GameObject> object);

	void notifyMapChanged();
	void validateInterceptors();
	void validateListeners();

	friend class GameBoardSerializer;

public:
	GameBoard(std::istream& is, InObjectsTable& table);
	void writeObject(std::ostream& os, OutObjectsTable& table);

	GameBoard(int width, int height, int screenWidth, int screenHeight);
	GameBoard(const GameBoard& from);
	virtual ~GameBoard();

	bool attach(shared_ptr<GameObject> object);
	void detach(shared_ptr<GameObject> object);
	bool detach(int objectId);

	void addInterceptor(shared_ptr<Interceptor> interceptor);
	void removeInterceptor(shared_ptr<Interceptor> interceptor);

	void addListener(BoardListener* listener);
	void removeListener(BoardListener* listener);

	const MouseTracker& mouseTracker() const;

	void onFrameStart();
	bool onEvent(sf::Event event);
	void onFrame(long timePassed);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void onFrameEnd();

	void onResize(int width, int height);

	void moveObject(int objectId, sf::Vector2i& from, sf::Vector2i& to);
	void moveObject(shared_ptr<GameObject>, sf::Vector2i& from, sf::Vector2i& to);

	Cell& getCell(const sf::Vector2i& coords) const; 
	bool hasCell(const sf::Vector2i& cellPosition) const;

	const BoardView& getView() const;

	GameController& getController();
	List<shared_ptr<GameObject>>& getChildren();

	void onClickLeft(sf::Vector2f& coords, bool wasPressed) override;
	void onMove(float dx, float dy) override;

	GameBoard* copy();
};

