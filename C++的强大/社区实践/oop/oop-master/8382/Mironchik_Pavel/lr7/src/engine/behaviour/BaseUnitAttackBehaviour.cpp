#include <cassert>
#include <typeinfo>

#include <GAME/engine/behaviour/BaseUnitAttackBehaviour.hpp>
#include <GAME/engine/Unit.hpp>
#include <GAME/utils/Utils.hpp>
#include <GAME/engine/GameBoard.hpp>
#include <GAME/engine/Cell.hpp>
#include <GAME/log/Log.hpp>

BaseUnitAttackBehaviour::BaseUnitAttackBehaviour() {}

BaseUnitAttackBehaviour::BaseUnitAttackBehaviour(Provider<Unit>* provider) {
	attach(provider);
}

bool BaseUnitAttackBehaviour::attack(sf::Vector2i &cell) {
	if (!isAttached()) {
		LogInfo info;
		info.name = "BaseUnitAttackBehaviour";
		info.pushParam("description", "Failed to attack: object is not attached");
		info.pushParam("cell", cell);
		Log::exception(info);
	}

	for (auto& object : provide().getBoard()->getCell(cell).objects()) {
		auto unit = dynamic_cast<Unit*>(object);

		if (unit != nullptr && attack(*unit))
			return true;
	}

	return false;
}

bool BaseUnitAttackBehaviour::attack(Unit& other) {
	if (!isAttached()) {
		LogInfo info;
		info.name = "BaseUnitAttackBehaviour";
		info.pushParam("description", "Failed to attack: behaviour is not attached");
		info.pushParam("target", other.toStringFull());
		Log::exception(info);
	}

	auto distance = Utils::computeMathDistance(provide().getOccupiedCell(), other.getOccupiedCell());

	if (distance > provide().getAttackRange())
		return false;

	if (other.getSquad() == provide().getSquad())
		return false;

	provide().getBoard()->getController().damageUnit(other, provide().getAttack());
	return true;
}