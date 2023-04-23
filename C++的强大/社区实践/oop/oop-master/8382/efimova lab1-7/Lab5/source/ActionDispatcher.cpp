#include "ActionDispatcher.h"
#include "PlayableBoardUnit.h"

ActionDispatcher::ActionDispatcher(Board* board) : mBoard(board) {
	
}

void ActionDispatcher::push_back(BoardUnit::ActionMeta meta) {
	actionQueue.push(meta);
}

std::vector<ActionDispatcher::Action>* ActionDispatcher::flush() {
	auto allActionsStack = new std::vector<Action>;
	//user move
	for (int i = 0; i < actionQueue.size(); i++) {
		auto meta = actionQueue.front();
		if (!meta.isEmpty) {

			Action action;
			auto fromUnitCoords = mBoard->getUnitCoords(meta.fromUnit);
			action.fromCell = fromUnitCoords;

			if (meta.isAttack || meta.isHeal) {

				auto fromUnit = dynamic_cast<PlayableBoardUnit*>(meta.fromUnit);
				auto toUnit = dynamic_cast<PlayableBoardUnit*>(meta.toUnit);

				action.fromCell = mBoard->getUnitCoords(fromUnit);
				action.toCell = mBoard->getUnitCoords(toUnit);
				action.actionType = "attack";
				allActionsStack->push_back(action);

				auto defendMetas = toUnit->defend(meta);

				if (!defendMetas[0].isEmpty) {
					for (int i = 0; i < defendMetas.size(); i++) {
						if (defendMetas[i].isAttack || defendMetas[i].isHeal) {

							auto toUnit = dynamic_cast<PlayableBoardUnit*>(defendMetas[i].toUnit);

							Action defendAction;
							defendAction.fromCell = mBoard->getUnitCoords(defendMetas[i].fromUnit);
							defendAction.toCell = mBoard->getUnitCoords(defendMetas[i].toUnit);
							defendAction.actionType = "attack";
							allActionsStack->push_back(defendAction);

							toUnit->defend(defendMetas[i]);
						}
					}
				}
			}
			else if (meta.isCreate) {
				mBoard->addUnit(meta.createdUnit, meta.unitX, meta.unitY);
				action.toCell = std::pair<int, int>(meta.unitX, meta.unitY);
				action.actionType = "create";
				allActionsStack->push_back(action);
			}
			else if (meta.isMove) {
				auto unit = meta.fromUnit;
				action.toCell = std::pair<int, int>(meta.moveX, meta.moveY);
				action.actionType = "move";
				allActionsStack->push_back(action);
				mBoard->moveUnit(unit, meta.moveX, meta.moveY);
			}
		}
		actionQueue.pop();
	}

	//turn moves
	for (int i = 0; i < mBoard->getBoardProperties().sizeY; i++) {
		for (int j = 0; j < mBoard->getBoardProperties().sizeX; j++) {
			auto cell = mBoard->getCellAt(j, i);
			auto metas = cell.terrainUnit->turnAction();
			if (!metas[0].isEmpty) {
				for (int k = 0; k < metas.size(); k++) {
					if (metas[k].isAttack || metas[k].isHeal) {
						auto toUnit = dynamic_cast<PlayableBoardUnit*>(metas[i].toUnit);
						
						Action action;
						action.fromCell = mBoard->getUnitCoords(metas[i].fromUnit);
						action.toCell = mBoard->getUnitCoords(metas[i].toUnit);
						action.actionType = "attack";

						toUnit->defend(metas[i]);
						allActionsStack->push_back(action);
					}
				}
			}
			else if(!cell.isEmpty) {
				auto _metas = cell.unit->turnAction();
				for (int k = 0; k < _metas.size(); k++) {
					if (_metas[k].isAttack || _metas[k].isHeal) {
						auto toUnit = dynamic_cast<PlayableBoardUnit*>(_metas[i].toUnit);

						Action action;
						action.fromCell = mBoard->getUnitCoords(_metas[i].fromUnit);
						action.toCell = mBoard->getUnitCoords(_metas[i].toUnit);
						action.actionType = "attack";

						toUnit->defend(_metas[i]);
						allActionsStack->push_back(action);
					}
				}
			}
		}
	}
	return allActionsStack;
}