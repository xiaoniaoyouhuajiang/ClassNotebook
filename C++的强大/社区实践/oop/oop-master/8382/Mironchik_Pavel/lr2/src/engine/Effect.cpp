#include <GAME/engine/Effect.hpp>
#include <GAME/engine/Unit.hpp>
#include <GAME/engine/GameBoard.hpp>

Effect::Effect(const Effect& other) {
	*this = other;
}

Effect::Effect(Effect::EffectName name) : _name(name) {}

Effect::EffectName Effect::name() const {
	return _name;
}

bool Effect::valid() {
	return _isValid;
}

void Effect::valid(bool valid) {
	_isValid = valid;
}

bool Effect::operator==(const Effect& other) {
	return name() == other.name();
}

Effect& Effect::operator=(const Effect& other) {
	_name = other._name;
	return *this;
}

void Effect::onObjectMoved(GameObject& object, sf::Vector2i& from, sf::Vector2i& to) {
	auto unit = dynamic_cast<Unit*>(&object);

	if (unit != origin())
		return;

	onOriginMoved(*unit, from, to);
}

void Effect::onObjectDetached(GameObject& object) {
	auto unit = dynamic_cast<Unit*>(&object);

	if (unit != origin())
		return;

	onOriginDetached(*unit);
}