#include <cmath>
#include <memory>

#include <GAME/engine/Neutral.hpp>
#include <GAME/utils/PathSearcher.hpp>
#include <GAME/engine/Unit.hpp>
#include <GAME/engine/GameBoard.hpp>
#include <GAME/graphics/CellDrawer.hpp>
#include <GAME/utils/Utils.hpp>

using std::abs;

Neutral::Neutral() : GameObject() {
	setFocusable(true);
	setTangible(true);
}

Neutral::Neutral(const Neutral& from) : GameObject(from) {
	_texture = from._texture;
}

void Neutral::effectDistance(int distance) {
	_effectDistance = distance;
}

int Neutral::effectDistance() {
	return _effectDistance;
}

void Neutral::texture(const sf::Texture* texture) {
	_texture = texture;
}

const sf::Texture* Neutral::texture() const {
	return _texture;
}

void Neutral::validateShapeDrawer() {
	PathSearcher searcher;
	searcher.computePaths(
		getOccupiedCell(),
		[this](sf::Vector2i& cellPosition) { return getBoard()->hasCell(cellPosition); },
		effectDistance()
	);
	VectorsSet<int> points;

	for (auto point : *searcher.getPaths())
		points.insert(point->coords);

	_shapeDrawer.setBoard(getBoard());
	_shapeDrawer.setPoints(points);
}

void Neutral::onObjectAttached(GameObject& object) {
	if (Utils::computeDistance(getOccupiedCell(), object.getOccupiedCell()) > effectDistance())
		return;

	try {
		onUnitEntered(dynamic_cast<Unit&>(object));
	}
	catch (...) {}
}

void Neutral::onObjectMoved(GameObject& object, sf::Vector2i& from, sf::Vector2i& to) {
	if (Utils::computeDistance(getOccupiedCell(), from) <= effectDistance())
		return;

	if (Utils::computeDistance(getOccupiedCell(), to) > effectDistance())
		return;
	
	try {
		onUnitEntered(dynamic_cast<Unit&>(object));
	}
	catch (...) {}
}

void Neutral::onAttach() {
	GameObject::onAttach();
	validateShapeDrawer();
}

void Neutral::onDetach() {
	GameObject::onDetach();
}

void Neutral::onDraw(sf::RenderTarget& target, sf::RenderStates states) const {
	if (_texture != nullptr) {
		TextureCellDrawer cellDrawer(*_texture);
		cellDrawer.set(getBoard()->getView(), getOccupiedCell());
		target.draw(cellDrawer);
	}

	if (isFocused())
		target.draw(_shapeDrawer, states);
}

bool Neutral::onClick(sf::Vector2i& cell) {
	if (isFocused()) {
		setFocused(false);
		return true;
	}
	else if (cell == getOccupiedCell()) {
		setFocused(true);
		return true;
	}

	return false;
}