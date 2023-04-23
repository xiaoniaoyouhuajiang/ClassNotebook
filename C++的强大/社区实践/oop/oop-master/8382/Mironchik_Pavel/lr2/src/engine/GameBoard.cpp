#include <GAME/engine/GameBoard.hpp>
#include <iostream>
#include <cassert>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <GAME/engine/BoardListener.hpp>

GameBoard::GameBoard(int width, int height, int screenWidth, int screenHeight) {
	_mouseTracker.setViewport(&view.viewport());
	cells = new Cell**[width];

	for (int i = 0; i < width; i++)
		cells[i] = new Cell*[height];

	for (int x = 0; x < width; x++)
		for (int y = 0; y < height; y++)
			cells[x][y] = new Cell(*this, sf::Vector2i(x, y));

	cellsCount = sf::Vector2i(width, height);
	onResize(screenWidth, screenHeight);
	controller = GameController(this);
}

GameBoard::GameBoard(const GameBoard& from) {
	view = BoardView(from.view);
	_mouseTracker.setViewport(&view.viewport());
	cellsCount = from.cellsCount;

	cells = new Cell**[cellsCount.x];

	for (int i = 0; i < cellsCount.x; i++)
		cells[i] = new Cell*[cellsCount.y];

	for (shared_ptr<GameObject> child : from.children)
		attach(child);

	controller = GameController(from.controller);
	controller.board = this;
}

GameBoard::~GameBoard() {
	for (int i = 0; i < cellsCount.x; i++)
		delete[] cells[i];

	delete[] cells;
	children.clear();
}

void GameBoard::addInterceptor(shared_ptr<Interceptor> interceptor) {
	if (interceptor->attachState == Interceptor::DETACHED)
		interceptors.add(interceptor);

	interceptor->attachState = Interceptor::ATTACHED;
}

void GameBoard::removeInterceptor(shared_ptr<Interceptor> interceptor) {
	interceptor->attachState = Interceptor::WAIT_FOR_DETACH;
}

void GameBoard::validateInterceptors() {
	interceptors.removeIf([](shared_ptr<Interceptor>& interceptor) {
		return interceptor->attachState == Interceptor::WAIT_FOR_DETACH;
	});
}

void GameBoard::validateListeners() {
	_listeners.removeIf([](shared_ptr<BoardListener>& listener) {
		if (listener->_attachState == BoardListener::WAIT_FOR_DETACH) {
			listener->_attachState = BoardListener::DETACHED;
			return true;
		}

		return false;
	});

	for (auto& listener : _listeners) 
		if (listener->_attachState == BoardListener::WAIT_FOR_ATTACH) 
			listener->_attachState = BoardListener::ATTACHED;
}

void GameBoard::onFrameStart() {
	validateInterceptors();
	validateListeners();

	bool mapChanged = false;

	children.removeIf([&mapChanged](shared_ptr<GameObject>& child) {
		if (child->attachState == GameObject::WAIT_FOR_DETACH) {
			child->detach();
			child->attachState = GameObject::DETACHED;
			mapChanged = true;
			return true;
		}

		return false;
	});

	for (shared_ptr<GameObject>& child : children) {
		if (child->attachState == GameObject::WAIT_FOR_ATTACH) {
			child->attachState = GameObject::ATTACHED;
			mapChanged = true;
		}
	}

	if (mapChanged) {
		notifyMapChanged();
	}

	for (shared_ptr<GameObject>& child : children) 
		if (child->attachState == GameObject::ATTACHED)
			child->onFrameStart();
}

List<shared_ptr<GameObject>>& GameBoard::getChildren() {
	return children;
}

const BoardView& GameBoard::getView() const {
	return view;
}

bool GameBoard::onEvent(sf::Event event) {
	if (_mouseTracker.processEvent(event))
		return true;

	if (event.type == sf::Event::MouseWheelScrolled
		&& event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
		view._viewport.setScale(view.viewport().getScale() + (float)event.mouseWheelScroll.delta);
		return true;
	}

	if (event.type == sf::Event::KeyReleased) {
		for (shared_ptr<Interceptor> interceptor : interceptors)
			if (interceptor->attachState == Interceptor::ATTACHED && interceptor->onInterceptKey(*this, event.key))
				return true;

		for (auto child : children) {
			if (child->isAttached() && child->onKeyPressed(event))
				return true;
		}
	}

	return false;
}

void GameBoard::onFrame(long timePassed) {
	for (shared_ptr<GameObject>& child : children) {
		if (child->attachState == GameObject::ATTACHED)
			child->onFrame(timePassed);
	}

	for (shared_ptr<GameObject>& child : children) {
		if (child->attachState == GameObject::ATTACHED)
			child->onPreDraw();
	}
}

void GameBoard::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (int x = 0; x < cellsCount.x; x++)
		for (int y = 0; y < cellsCount.y; y++)
			target.draw(*cells[x][y]);

	target.draw(view.gridDrawer(), states);

	for (auto child : children)
		if (child->attachState == GameObject::ATTACHED)
			child->onDraw(target, states);
}

void GameBoard::onFrameEnd() {
	for (auto child : children)
		if (child->attachState == GameObject::ATTACHED)
			child->onFrameEnd();
}

bool GameBoard::attach(shared_ptr<GameObject> object) {
	if (object->isAttached())
		return false;

	children.add(object);
	object->attach(this);
	addListener(object);
	object->attachState = GameObject::WAIT_FOR_ATTACH;
	Cell& cell = getCell(object->getOccupiedCell());
	cell.add(object);
	notifyObjectAttached(object);
	return true;
}

void GameBoard::detach(shared_ptr<GameObject> object) {
	if (!object->isAttached())
		return;

	Cell& cell = getCell(object->getOccupiedCell());
	cell.remove(object);
	removeListener(object);
	object->attachState = GameObject::WAIT_FOR_DETACH;
	notifyObjectDetached(object);
}

bool GameBoard::detach(int objectId) {
	for (auto& object : children) {
		if (object->id() == objectId) {
			detach(object);
			return true;
		}
	}

	return false;
}

GameController& GameBoard::getController() {
	return controller;
}

void GameBoard::onResize(int width, int height) {
	float side = fminf(((float)width) / cellsCount.x, ((float)height) / cellsCount.y);
	view.update(sf::Vector2f((float)width, (float)height), cellsCount);
}

void GameBoard::moveObject(int objectId, sf::Vector2i& from, sf::Vector2i& to) {
	for (auto& child : children) {
		if (child->id() == objectId)
			return moveObject(child, from, to);
	}
}

void GameBoard::moveObject(shared_ptr<GameObject> object, sf::Vector2i& from, sf::Vector2i& to) {
	(*cells[from.x][from.y]).remove(object);
	(*cells[to.x][to.y]).add(object);
	notifyMapChanged();
	if (object->isAttached())
		notifyObjectMoved(object, from, to);
}

Cell& GameBoard::getCell(const sf::Vector2i& coords) const {
	if (!hasCell(coords))
		return trashCell;

	return *cells[coords.x][coords.y];
}

bool GameBoard::hasCell(const sf::Vector2i& cellPosition) const {
	return cellPosition.x >= 0 && cellPosition.x < cellsCount.x
		&& cellPosition.y >= 0 && cellPosition.y < cellsCount.y;
}

void GameBoard::onClickLeft(sf::Vector2f& coords, bool wasMoved) {
	if (wasMoved)
		return;

	for (shared_ptr<Interceptor> interceptor : interceptors)
		if (interceptor->attachState == Interceptor::ATTACHED && interceptor->onInterceptLeftClick(*this, coords))
			return;

	sf::Vector2i cellPosition = view.mapCoordsToCell(coords);

	if (!hasCell(cellPosition))
		return;

	bool processed = false;

	for (shared_ptr<GameObject> child : children) {
		if (child->isAttached() && child->isFocused())
			processed |= child->onClick(cellPosition);
	}

	if (processed)
		return;

	for (shared_ptr<GameObject>& child : children)
		if (child->isAttached() && !child->isFocused() && child->onClick(cellPosition))
			return;
}

void GameBoard::onMove(float dx, float dy) {
	if (!_mouseTracker.isLeftPressed())
		return;

	view._viewport.move(-dx, -dy);
}

void GameBoard::notifyMapChanged() {
	for (auto child : children)
		child->onMapChanged();
}

GameBoard* GameBoard::copy() {
	return new GameBoard(*this);
}

void GameBoard::addListener(shared_ptr<BoardListener> listener) {
	assert(listener->_attachState == BoardListener::DETACHED || _listeners.contains(listener));
	listener->_attachState = BoardListener::WAIT_FOR_ATTACH;

	std::cout << "Add listener " << listener << std::endl;

	if (!_listeners.contains(listener))
		_listeners.add(listener);
}

void GameBoard::removeListener(shared_ptr<BoardListener> listener) {
	assert(_listeners.contains(listener));
	listener->_attachState = BoardListener::WAIT_FOR_DETACH;

	std::cout << "Remove listener" << listener << std::endl;
}

const MouseTracker& GameBoard::mouseTracker() const {
	return _mouseTracker;
}

void GameBoard::notifyObjectAttached(shared_ptr<GameObject> object) {
	for (auto listener : _listeners)
		if (listener->_attachState == BoardListener::ATTACHED)
			listener->onObjectAttached(*object);
}

void GameBoard::notifyObjectMoved(shared_ptr<GameObject> object, sf::Vector2i& from, sf::Vector2i& to) {
	for (auto listener : _listeners)
		if (listener->_attachState == BoardListener::ATTACHED)
			listener->onObjectMoved(*object, from, to);
}

void GameBoard::notifyObjectDetached(shared_ptr<GameObject> object) {
	for (auto listener : _listeners)
		if (listener->_attachState == BoardListener::ATTACHED)
			listener->onObjectDetached(*object);
}
