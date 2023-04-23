#include <GAME/controller/PlayerState.hpp>
#include <GAME/engine/GameBoard.hpp>
#include <GAME/engine/Unit.hpp>


PlayerState::PlayerState(int squad) : _squad(squad) {}

int PlayerState::squad() {
	return _squad;
}

bool PlayerState::isOver(GameBoard* board) {
	int unitsCount = 0;

	for (auto object : board->getChildren()) {
		if (!object->isAttached())
			continue;

		Unit* unit = dynamic_cast<Unit*>(object.get());

		if (unit != nullptr && unit->getSquad() == _squad)
			unitsCount++;
	}

	return unitsCount == 0;
}