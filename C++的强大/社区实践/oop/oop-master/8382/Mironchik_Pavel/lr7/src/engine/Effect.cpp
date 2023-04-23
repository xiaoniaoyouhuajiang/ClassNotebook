#include <GAME/engine/Effect.hpp>
#include <GAME/engine/Unit.hpp>
#include <GAME/engine/GameBoard.hpp>
#include <GAME/engine/terrains/GroundTerrain.hpp>
#include <GAME/engine/units/Heal.hpp>
#include <GAME/engine/units/Chancel.hpp>
#include <GAME/engine/units/BlackHole.hpp>

Effect* Effect::readObject(istream& is, InObjectsTable& table) {
	int rawName;
	Serializer::readInt(is, &rawName);
	EffectName name = static_cast<EffectName>(rawName);

	if (name == LAVA_EFFECT)
		return new LavaEffect(is, table);

	if (name == SEA_EFFECT)
		return new SeaEffect(is, table);

	if (name == GROUND_EFFECT) {
		Log::exception("Effect", "Failed to read object from file: GROUND_EFFECT is not exists now");
		return nullptr;
	}

	if (name == HEAL_EFFECT)
		return new HealEffect(is, table);

	if (name == CHANCEL_EFFECT)
		return new ChancelEffect(is, table);

	if (name == BLACK_HOLE_EFFECT)
		return new BlackHoleEffect(is, table);

	LogInfo info;
	info.name = "Effect";
	info.pushParam("nameId", std::to_string(name));
	info.pushParam("description", "Failed to read object from file: GROUND_EFFECT is not exists now");
	Log::exception(info);
	return nullptr;
}


void Effect::writeObject(ostream& os, OutObjectsTable& table, Effect* effect) {
	int rawName = static_cast<int>(effect->_name);
	Serializer::writeInt(os, &rawName);
	effect->writeObject(os, table);
}

Effect::Effect(istream& is, InObjectsTable& table) {
	int rawName;
	Serializer::readInt(is, &rawName);
	_name = static_cast<EffectName>(rawName);
	Serializer::readBool(is, &_isValid);
	readAttachable(is, table);
	readBoardListener(is, table);
}

void Effect::writeObject(ostream& os, OutObjectsTable& table) {
	int rawName = static_cast<int>(_name);
	Serializer::writeInt(os, &rawName);
	Serializer::writeBool(os, &_isValid);
	writeAttachable(os, table);
	writeBoardListener(os, table);
}

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