#include "SetTowerCommand.h"
#include "LogerAdapter.h"



SetTowerCommand::SetTowerCommand(std::shared_ptr<Field> field) : Command(field)
{
}


SetTowerCommand::~SetTowerCommand()
{
}

void SetTowerCommand::execute(std::shared_ptr<Request> request)
{
	field->createTower(request->coordX1, request->coordY1, request->factory);
	field->getMediator()->getLoger()->logAboutCreatedTower(request->coordX1, request->coordY1);
	field->getMediator()->getLoger()->logTowerStatus(field->getCell(request->coordX1, request->coordY1)->getTower());
	field->printField();
}
