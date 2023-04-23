#include "AttackCommand.h"



AttackCommand::AttackCommand(std::shared_ptr<Field> field):Command(field)
{
}


AttackCommand::~AttackCommand()
{
}

void AttackCommand::execute(std::shared_ptr<Request> request)
{
	field->getCell(request->coordX1, request->coordY1)->getUnit()->performAttack();
}
