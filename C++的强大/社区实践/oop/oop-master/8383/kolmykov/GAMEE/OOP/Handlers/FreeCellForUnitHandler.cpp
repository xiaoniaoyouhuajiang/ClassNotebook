#include "FreeCellForUnitHandler.h"
#include "LogerAdapter.h"



FreeCellForUnitHandler::FreeCellForUnitHandler(std::shared_ptr<Field> field):Handler(field) {
}


FreeCellForUnitHandler::~FreeCellForUnitHandler()
{
}

void FreeCellForUnitHandler::handle(std::shared_ptr<Request> request) {
	if (!field->getCell(request->coordX2, request->coordY2)->hasTower() && !field->getCell(request->coordX2, request->coordY2)->hasUnit()) {
		if (nextHandler != nullptr) {
			nextHandler->handle(request);
		}
	}
	else {
		field->getMediator()->getLoger()->logAboutCellIsEngaged();
	}
}
