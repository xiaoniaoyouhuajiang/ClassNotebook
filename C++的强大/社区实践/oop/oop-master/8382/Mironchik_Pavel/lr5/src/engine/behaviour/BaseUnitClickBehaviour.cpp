#include <cassert>

#include <GAME/engine/behaviour/BaseUnitClickBehaviour.hpp>
#include <GAME/engine/Unit.hpp>
#include <GAME/engine/behaviour/BaseUnitAttackBehaviour.hpp>
#include <GAME/engine/behaviour/BaseUnitMoveBehaviour.hpp>

BaseUnitClickBehaviour::BaseUnitClickBehaviour() {}

BaseUnitClickBehaviour::BaseUnitClickBehaviour(Provider<Unit>* provider) {
	attach(provider);
}

bool BaseUnitClickBehaviour::onCellClick(sf::Vector2i &cell) {
	assert(isAttached());

	Unit& me = provide();

	if (!me.isFocused()) {
		if (cell == me.getOccupiedCell()) {
			me.setFocused(true);
			return true;
		}

		return false;
	}

	provide().attackBehaviour()->attack(cell) || provide().moveBehaviour()->move(cell);
	provide().setFocused(false);
	return true;
}