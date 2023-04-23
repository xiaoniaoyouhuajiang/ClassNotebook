#include "CreateUnitCommand.h"
#include "LogerAdapter.h"


CreateUnitCommand::CreateUnitCommand(std::shared_ptr<Field> field):Command(field)
{
}


CreateUnitCommand::~CreateUnitCommand() {
}

void CreateUnitCommand::execute(std::shared_ptr<Request> request)
{
	std::shared_ptr<Unit> unit = field->getCell(request->coordX1, request->coordY1)->getTower()->createUnit(request->coordX2, request->coordY2, field->getCell(request->coordX1, request->coordY1)->getTower()->getLevel());
	field->getCell(request->coordX2, request->coordY2)->setUnit(unit);
    field->getCell(request->coordX2, request->coordY2)->getLand()->bufUnit(unit);
	field->getMediator()->getLoger()->logAboutCreatedUnit(request->coordX2, request->coordY2);
	field->getMediator()->getLoger()->logUnitStatus(unit);
	field->printField();
}
