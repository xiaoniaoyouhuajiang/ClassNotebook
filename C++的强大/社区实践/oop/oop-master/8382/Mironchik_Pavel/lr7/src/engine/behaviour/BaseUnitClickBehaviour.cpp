#include <cassert>

#include <GAME/engine/behaviour/BaseUnitClickBehaviour.hpp>
#include <GAME/engine/Unit.hpp>
#include <GAME/engine/behaviour/BaseUnitAttackBehaviour.hpp>
#include <GAME/engine/behaviour/BaseUnitMoveBehaviour.hpp>
#include <GAME/controller/GameController.hpp>

BaseUnitClickBehaviour::BaseUnitClickBehaviour() {}

BaseUnitClickBehaviour::BaseUnitClickBehaviour(Provider<Unit>* provider) {
	attach(provider);
}

bool BaseUnitClickBehaviour::onCellClick(sf::Vector2i &cell) {
	if (!isAttached()) {
		LogInfo info;
		info.name = "BaseUnitClickBehaviour";
		info.pushParam("description", "Failed to process click: behaviour is not attached");
		info.pushParam("cell", cell);
		Log::exception(info);
	}

	Unit& me = provide();

	if (GameController::instance()->currentState().squad() != me.getSquad()) {
		me.setFocused(false);
		return false;
	}

	if (!me.isFocused()) {
		if (cell == me.getOccupiedCell()) {
			me.setFocused(true);
			return true;
		}

		return false;
	}

	if (provide().attackBehaviour()->attack(cell) || provide().moveBehaviour()->move(cell)) {
		GameController::instance()->step();
	}

	provide().setFocused(false);
	return true;
}