#include "UnitExistenceHandler.h"
#include "LogerAdapter.h"


UnitExistenceHandler::UnitExistenceHandler(std::shared_ptr<Field> field) : Handler(field) {

}


UnitExistenceHandler::~UnitExistenceHandler()
{
}

void UnitExistenceHandler::handle(std::shared_ptr<Request> request) {
	if (field->getCell(request->coordX1, request->coordY1)->getUnit() != nullptr) {
		if (nextHandler != nullptr) {
			nextHandler->handle(request);
		}
	}
	else {
		field->getMediator()->getLoger()->logAboutUnitNotExist();
	}
}
