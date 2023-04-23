#include <GAME/engine/Unit.hpp>
#include <GAME/engine/GameObject.hpp>
#include <GAME/engine/GameBoard.hpp>
#include <cmath>

Unit::Unit(int squad) : GameObject() {
	setFocusable(true);
	this->squad = squad;
}

Unit::Unit(const Unit& from) : GameObject(from) {
	_properties = from._properties;
	squad = from.squad;
	textureDrawer = from.textureDrawer;
}

Unit::~Unit() {
	delete attackCells;
};

int Unit::distanceTo(const sf::Vector2i& position) const {
	if (!getBoard()->hasCell(getOccupiedCell()) || !getBoard()->hasCell(position))
		return 99999;

	sf::Vector2i& point1 = getOccupiedCell();

	return std::labs(point1.x - position.x) + std::labs(point1.y - position.y);
}

void Unit::drawAchievableCells(sf::RenderTarget& target, sf::RenderStates states) const {
	validatePathSearcher();

	for (PathPoint* point : *pathSearcher.getPaths()) {
		achievableDrawer.set(getBoard()->getView(), point->coords);
		target.draw(achievableDrawer);
	}
}

void Unit::drawAttackCells(sf::RenderTarget& target, sf::RenderStates states) const {
	validateAttackCells();

	for (sf::Vector2i& cellPosition: *attackCells) {
		attackDrawer.set(getBoard()->getView(), cellPosition);
		target.draw(attackDrawer);
	}
}


void Unit::drawHealth(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(_healthDrawer, states);
}

void Unit::validateAttackCells() const {
	if (attackCells == nullptr)
		attackCells = computeAttackCells();
}

List<sf::Vector2i>* Unit::computeAttackCells() const {
	List<sf::Vector2i>* cells = new List<sf::Vector2i>();
	sf::Vector2i& myCell = getOccupiedCell();
	int range = getAttackRange();
	for (int x = myCell.x - range; x <= myCell.x + range; x++) {
		for (int y = myCell.y - range; y <= myCell.y + range; y++) {
			sf::Vector2i cellPosition(x, y);

			if (distanceTo(cellPosition) > _curProperties.attackRange())
				continue;

			if (!getBoard()->hasCell(cellPosition))
				continue;

			if (canAttack(cellPosition))
				cells->add(cellPosition);
		}
	}
	return cells;
}

void Unit::setHealth(float health) {
	_properties.health(health);
	transformProperties();
}

float Unit::getHealth() const {
	return std::min(_curProperties.health(), _curProperties.maxHealth());
}

void Unit::setMaxHealth(float maxHealth) {
	_properties.maxHealth(maxHealth);
	_properties.health(maxHealth);
	transformProperties();
}

float Unit::getMaxHealth() const {
	return _curProperties.maxHealth();
}

void Unit::setAttack(float attack) {
	_properties.attack(attack);
	transformProperties();
}

float Unit::getAttack() const {
	return _curProperties.attack();
}

void Unit::setAttackRange(float attackRange) {
	_properties.attackRange(attackRange);
	transformProperties();
}

float Unit::getAttackRange() const {
	return _curProperties.attackRange();
}

void Unit::setSpeed(int speed) {
	this->_properties.speed(speed);
	transformProperties();
}

int Unit::getSpeed() const {
	return _curProperties.speed();
}

int Unit::getSquad() const {
	return squad;
}

void Unit::drawTexture(sf::RenderTarget& target, sf::RenderStates states) const {
	textureDrawer.set(getBoard()->getView(), getOccupiedCell());
	target.draw(textureDrawer);
}

bool Unit::canGoToCell(const GameBoard& board, const sf::Vector2i& cellPosition) const {
	const Cell& cell = board.getCell(cellPosition);
	for (auto object : cell.objects())
		if (object->isTangible())
			return false;

	return board.hasCell(cellPosition);
}

bool Unit::canAttack(const sf::Vector2i& cellPosition) const {
	for (auto object : getBoard()->getCell(cellPosition).objects()) {
		Unit* unit = dynamic_cast<Unit*>(object.get());
		if (unit != nullptr && unit->getSquad() != getSquad())
			return true;
	}

	return false;
}

void Unit::onMapChanged() {
	pathSearcher.clear();

	if (attackCells != nullptr)
		delete attackCells;

	attackCells = nullptr;
}

// must call super
void Unit::onDraw(sf::RenderTarget& target, sf::RenderStates states) const {
	if (isFocused()) {
		drawAchievableCells(target, states);
		drawAttackCells(target, states);
	}
	drawTexture(target, states);
	drawHealth(target, states);
}

void Unit::setTexture(sf::Texture& texture) {
	textureDrawer.setTexture(texture);
}

void Unit::validatePathSearcher() const {
	if (pathSearcher.getPaths() == nullptr)
		pathSearcher.computePaths(
			getOccupiedCell(),
			[this](sf::Vector2i& cellPosition) { return this->canGoToCell(*getBoard(), cellPosition); },
			getSpeed()
		);
}

bool Unit::onClick(sf::Vector2i& cell) {
	validatePathSearcher();
	if (isFocused()) {
		if (cell == getOccupiedCell()) {
			setFocused(false);
			return true;
		}

		for (PathPoint* point : *pathSearcher.getPaths()) {
			if (point->coords == cell) {
				setOccupiedCell(cell);
				setFocused(false);
				return true;
			}
		}

		// TODO process attacks

		setFocused(false);

		return true;
	}

	if (cell != getOccupiedCell())
		return false;

	setFocused(true);
	return true;
}

GameObject* Unit::copy() {
	return new Unit(*this);
}

int Unit::info() const {
	return Info::UNKNOWN;
}

void Unit::addEffect(shared_ptr<Effect> effect) {
	if (_effects.count(effect))
		return;
	
	_effects.insert(effect);
	effect->attach(this);
	getBoard()->addListener(effect);
	transformProperties();
}

void Unit::removeEffect(shared_ptr<Effect> effect) {
	assert(effect->valid() && effect->origin() == this);
	getBoard()->removeListener(effect);
	effect->detach();
	_effects.erase(effect);
	transformProperties();
}

void Unit::removeEffect(Effect::EffectName effectName) {
	try {
		auto effect = _effects.find(effectName);
		removeEffect(effect);
	} catch (...) {}
}

void Unit::transformProperties() {
	_curProperties = _properties;

	for (shared_ptr<Effect> effect : _effects)
		_curProperties.transform(*effect);
}

void Unit::onAttach() {

}

void Unit::onDetach() {
	for (auto effect : _effects) {
		getBoard()->removeListener(effect);
		effect->detach();
	}

	_effects.clear();
}