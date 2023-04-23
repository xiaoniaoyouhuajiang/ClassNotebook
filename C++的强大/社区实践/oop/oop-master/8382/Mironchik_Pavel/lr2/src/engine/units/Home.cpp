#include <GAME/engine/units/Home.hpp>
#include <GAME/engine/GameBoard.hpp>
#include <GAME/graphics/BoardView.hpp>
#include <GAME/graphics/Viewport.hpp>


Home::Home(int squad) : Unit(squad), _selectedUnitInstance(shared_ptr<Unit>(new BumSoldier(squad))) {
	_keyToUnit.clear();
	_keyToUnit[sf::Keyboard::Num1] = Info::BUM_SOLDIER;
	_keyToUnit[sf::Keyboard::Num2] = Info::CLEVER_TOWER;
	_keyToUnit[sf::Keyboard::Num3] = Info::MOUNTED_WARRIOR;
	_keyToUnit[sf::Keyboard::Num4] = Info::MOUNTED_SHOOTER;
	_keyToUnit[sf::Keyboard::Num5] = Info::PEASANT;
	_keyToUnit[sf::Keyboard::Num6] = Info::STRONG_TOWER;
	setTexture(Textures::getInstance().home());
	setMaxHealth(50);
}

Home::Home(const Home& from) : Unit(from), _selectedUnitInstance(shared_ptr<Unit>(new BumSoldier(from.getSquad()))) {
	_keyToUnit = from._keyToUnit;
	setTexture(Textures::getInstance().home());
}

Home::~Home() {

}

bool Home::onClick(sf::Vector2i& cell) {
	if (!isFocused()) {
		if (cell == getOccupiedCell()) {
			setFocused(true);
			validateSelectedUnitInstance();
			return true;
		}

		return false;
	}

	setFocused(false);

	if (_selectedUnitInstance->canGoToCell(*getBoard(), cell) && _children.size() < MAX_UNITS_COUT) {
		getBoard()->getController().addUnit(_selectedUnitInstance, cell);
		_selectedUnitInstance = getBoard()->getController().createUnit(_selectedUnit, getSquad());
	}

	return true;
}

bool Home::onKeyPressed(sf::Event keyEvent) {
	if (!isFocused())
		return false;

	if (_keyToUnit.count(keyEvent.key.code)) {
		_selectedUnit = _keyToUnit[keyEvent.key.code];
		validateSelectedUnitInstance();
		return true;
	}

	if (keyEvent.key.code == sf::Keyboard::Escape) {
		setFocused(false);
		return true;
	}

	return false;
}

void Home::onDraw(sf::RenderTarget& target, sf::RenderStates states) const {
	drawTexture(target, states);
	drawHealth(target, states);
	
	sf::Vector2i cell = getBoard()->getView().mapPixelsToCell(getBoard()->mouseTracker().getLastPixels());

	if (isFocused()) {
		ColorCellDrawer cellDrawer(sf::Color(77, 173, 238, 100));
		cellDrawer.set(getBoard()->getView(), getOccupiedCell());
		target.draw(cellDrawer, states);
	}

	if (isFocused() && _selectedUnitInstance->canGoToCell(*getBoard(), cell) && _children.size() < MAX_UNITS_COUT) {
		TextureCellDrawer unitDrawer(*Info::instance().getTextureByInfo(_selectedUnit));
		ColorCellDrawer cellDrawer(sf::Color(156, 215, 247, 50));

		unitDrawer.set(getBoard()->getView(), cell);
		target.draw(unitDrawer, states);

		cellDrawer.set(getBoard()->getView(), cell);
		target.draw(cellDrawer, states);
	}
}

void Home::onAttach() {
	Unit::onAttach();
	_children.clear();
	for (auto object : getBoard()->getChildren()) {
		if (object->id() == id())
			continue;

		auto unit = dynamic_cast<Unit*>(object.get());

		if (unit != nullptr && unit->getSquad() == getSquad())
			_children.insert(unit->id());
	}
}

void Home::onDetach() {
	Unit::onDetach();
	for (auto child : _children) {
		getBoard()->getController().removeUnit(child);
	}
}

void Home::onObjectAttached(GameObject& object) {
	try {
		Unit& unit = dynamic_cast<Unit&>(object);

		if (unit.getSquad() == getSquad())
			_children.insert(object.id());
	}
	catch (...) {

	}
}

void Home::onObjectDetached(GameObject& object) {
	try {
		Unit& unit = dynamic_cast<Unit&>(object);

		if (unit.getSquad() == getSquad())
			_children.erase(object.id());
	}
	catch (...) {

	}
}

void Home::validateSelectedUnitInstance() {
	if (_selectedUnit == _selectedUnitInstance->info()
		&& !_selectedUnitInstance->isAttached())
		return;

	_selectedUnitInstance = getBoard()->getController().createUnit(_selectedUnit, getSquad());
}

int Home::info() const {
	return Info::HOME;
}