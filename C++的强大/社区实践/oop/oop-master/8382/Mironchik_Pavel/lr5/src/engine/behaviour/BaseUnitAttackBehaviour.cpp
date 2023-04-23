#include <cassert>

#include <GAME/engine/behaviour/BaseUnitAttackBehaviour.hpp>
#include <GAME/engine/Unit.hpp>
#include <GAME/utils/Utils.hpp>
#include <GAME/engine/GameBoard.hpp>
#include <GAME/engine/Cell.hpp>

BaseUnitAttackBehaviour::BaseUnitAttackBehaviour() {}

BaseUnitAttackBehaviour::BaseUnitAttackBehaviour(Provider<Unit>* provider) {
	attach(provider);
}

bool BaseUnitAttackBehaviour::attack(sf::Vector2i &cell) {
	assert(isAttached());

	for (auto& object : provide().getBoard()->getCell(cell).objects()) {
		auto unit = dynamic_cast<Unit*>(object);

		if (unit != nullptr && attack(*unit))
			return true;
	}

	return false;
}

bool BaseUnitAttackBehaviour::attack(Unit& other) {
	assert(isAttached());

	auto distance = Utils::computeMathDistance(provide().getOccupiedCell(), other.getOccupiedCell());

	if (distance > provide().getAttackRange())
		return false;

	if (other.getSquad() == provide().getSquad())
		return false;

	provide().getBoard()->getController().damageUnit(other, provide().getAttack());
	return true;
}