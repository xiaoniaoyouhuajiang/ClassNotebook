#include "TowerExistenceHandler.h"
#include "LogerAdapter.h"



TowerExistenceHandler::TowerExistenceHandler(std::shared_ptr<Field> field) : Handler(field) {

}


TowerExistenceHandler::~TowerExistenceHandler()
{
}

void TowerExistenceHandler::handle(std::shared_ptr<Request> request) {
	if (field->getCell(request->coordX1, request->coordY1)->hasTower()) {
		if (nextHandler != nullptr) {
			nextHandler->handle(request);
		}
	}
	else {
		field->getMediator()->getLoger()->logAboutTowerNotExist();
	}
}
