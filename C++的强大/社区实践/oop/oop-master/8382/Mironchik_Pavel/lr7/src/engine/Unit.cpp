#include <GAME/engine/Unit.hpp>
#include <GAME/engine/GameObject.hpp>
#include <GAME/engine/GameBoard.hpp>
#include <GAME/graphics/ShapeDrawer.hpp>
#include <GAME/utils/Utils.hpp>
#include <GAME/controller/GameController.hpp>
#include <cmath>

Unit::Unit(istream& is, InObjectsTable& table) : GameObject(is, table) {
	_properties = Properties(is, table);
	_curProperties = Properties(is, table);
	Serializer::readInt(is, &squad);
	_effects.readSet(is, table);
	textureDrawer.setTexture(*Textures::readTexture(is, table));
}

void Unit::writeObject(ostream& os, OutObjectsTable& table) {
	GameObject::writeObject(os, table);
	_properties.writeObject(os, table);
	_curProperties.writeObject(os, table);
	Serializer::writeInt(os, &squad);
	_effects.writeSet(os, table);
	Textures::writeTexture(os, table, textureDrawer.getTexture());
}

Unit::Unit(int squad) : GameObject() {
	setFocusable(true);
	this->squad = squad;
}

Unit::Unit(const Unit& from) : GameObject(from) {
	_properties = from._properties;
	squad = from.squad;
	textureDrawer = from.textureDrawer;
	_clickBehaviour = from._clickBehaviour;
	_moveBehaviour = from._moveBehaviour;
	_attackBehaviour = from._attackBehaviour;
}

Unit::~Unit() {
	for (auto effect : _effects) {
		delete effect;
	}
	delete attackCells;
};

Unit& Unit::provide() {
	return *this;
}

int Unit::distanceTo(const sf::Vector2i& position) const {
	if (!getBoard()->hasCell(getOccupiedCell()) || !getBoard()->hasCell(position))
		return 99999;

	sf::Vector2i& point1 = getOccupiedCell();

	return std::labs(point1.x - position.x) + std::labs(point1.y - position.y);
}

void Unit::drawAchievableCells(sf::RenderTarget& target, sf::RenderStates states) const {
	ShapeDrawer drawer;
	drawer.setBoard(getBoard());
	drawer.setPoints(_moveBehaviour->availableCells());
	drawer.setBorderColor(sf::Color(0, 0, 0, 0));
	target.draw(drawer, states);
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
			auto cell = sf::Vector2i(x, y);
			auto distance = Utils::computeMathDistance(cell, myCell);

			if (distance > _curProperties.attackRange())
				continue;

			if (!getBoard()->hasCell(cell))
				continue;

			if (canAttack(cell))
				cells->add(cell);
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
		Unit* unit = dynamic_cast<Unit*>(object);
		if (unit != nullptr && unit->getSquad() != getSquad())
			return true;
	}

	return false;
}

void Unit::onMapChanged() {
	_moveBehaviour->computeAvailableCells();

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

bool Unit::onClick(sf::Vector2i& cell) {
	_moveBehaviour->computeAvailableCells();
	return _clickBehaviour->onCellClick(cell);
}

GameObject* Unit::copy() {
	return new Unit(*this);
}

int Unit::info() const {
	return Info::UNKNOWN;
}

void Unit::addEffect(Effect* effect) {
	if (_effects.count(effect))
		return;
	
	_effects.insert(effect);
	effect->attach(this);
	getBoard()->addListener(effect);
	transformProperties();
}

void Unit::removeEffect(Effect* effect) {
	if (!(effect->valid() && effect->origin() == this)) {
		LogInfo info;
		info.name = "Unit";
		info.pushParam("me", toStringFull());
		info.pushParam("description", "Failed to remove effect: effect is not belong to unit's effects");
		Log::exception(info);
	}

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

	for (Effect* effect : _effects)
		_curProperties.transform(*effect);

	if (isAttached())
		_moveBehaviour->computeAvailableCells();
}

void Unit::onAttach() {
	_moveBehaviour->computeAvailableCells();
}

void Unit::onDetach() {
	for (auto effect : _effects) {
		getBoard()->removeListener(effect);
		effect->detach();
	}

	_effects.clear();
}

void Unit::attackBehaviour(shared_ptr<UnitAttackBehaviour> attackBehaviour) {
	_attackBehaviour->detach();
	_attackBehaviour = attackBehaviour;
	_attackBehaviour->attach(this);
}

shared_ptr<UnitAttackBehaviour> Unit::attackBehaviour() {
	return _attackBehaviour;
}

void Unit::moveBehaviour(shared_ptr<UnitMoveBehaviour> moveBehaviour) {
	_moveBehaviour->detach();
	_moveBehaviour = moveBehaviour;
	_moveBehaviour->attach(this);
}

shared_ptr<UnitMoveBehaviour> Unit::moveBehaviour() {
	return _moveBehaviour;
}

void Unit::fillLogInfo(LogInfo& info) {
	GameObject::fillLogInfo(info);
	info.name = "Unit";
	info.pushParam("properties", _properties.toStringFull());
	info.pushParam("efffectsCount", std::to_string(_effects.size()));
}