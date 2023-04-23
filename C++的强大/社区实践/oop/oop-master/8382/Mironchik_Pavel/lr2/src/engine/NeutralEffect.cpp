#include <GAME/engine/NeutralEffect.hpp>
#include <GAME/engine/Unit.hpp>
#include <GAME/engine/GameBoard.hpp>
#include <GAME/utils/Utils.hpp>

NeutralEffect::NeutralEffect(EffectName effectName, int neutralInfo, int distance) :
	Effect(effectName),
	_neutralInfo(neutralInfo),
	_distance(distance) {}

NeutralEffect::NeutralEffect(const NeutralEffect& from) : Effect(from) {
	_neutralInfo = from._neutralInfo;
	_distance = from._distance;
}

void NeutralEffect::onOriginMoved(Unit& origin, sf::Vector2i& from, sf::Vector2i& to) {
	for (auto object : origin.getBoard()->getChildren()) {
		if (object->info() != _neutralInfo)
			continue;

		if (Utils::computeDistance(origin.getOccupiedCell(), object->getOccupiedCell()) <= _distance)
			return;
	}

	origin.removeEffect(name());
}
void NeutralEffect::onOriginDetached(Unit& origin) {
	origin.removeEffect(name());
}