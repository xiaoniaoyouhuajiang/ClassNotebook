#include "MoveCommand.h"



MoveCommand::MoveCommand(std::shared_ptr<Field> field) : Command(field) {
}


MoveCommand::~MoveCommand()
{
}

void MoveCommand::execute(std::shared_ptr<Request> request) {
	field->getCell(request->coordX1, request->coordY1)->getUnit()->performMove();
}
