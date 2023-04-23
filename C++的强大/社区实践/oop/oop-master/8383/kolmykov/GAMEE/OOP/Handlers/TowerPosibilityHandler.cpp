#include "TowerPosibilityHandler.h"
#include "LogerAdapter.h"


TowerPosibilityHandler::TowerPosibilityHandler(std::shared_ptr<Field> field):Handler(field)
{
}


TowerPosibilityHandler::~TowerPosibilityHandler()
{
}

void TowerPosibilityHandler::handle(std::shared_ptr<Request> request) {
	if (field->getCell(request->coordX1, request->coordY1)->getTower()->canCreateUnit()) {
		if (nextHandler != nullptr) {
			nextHandler->handle(request);
		}
	}
	else {
		field->getMediator()->getLoger()->logAboutTowwerNotPossible();
	}
}
