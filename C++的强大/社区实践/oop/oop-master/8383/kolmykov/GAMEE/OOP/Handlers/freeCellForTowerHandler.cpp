#include "freeCellForTowerHandler.h"
#include "LogerAdapter.h"


FreeCellForTowerHandler::FreeCellForTowerHandler(std::shared_ptr<Field> field) : Handler(field) {

}


FreeCellForTowerHandler::~FreeCellForTowerHandler()
{
}

void FreeCellForTowerHandler::handle(std::shared_ptr<Request> request) {
	if (!field->getCell(request->coordX1, request->coordY1)->hasTower() && !field->getCell(request->coordX1, request->coordY1)->hasUnit()) {
		if (nextHandler != nullptr) {
			nextHandler->handle(request);
		}
	}
	else {
		field->getMediator()->getLoger()->logAboutCellIsEngaged();
	}
}
