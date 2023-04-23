#include "FinalMoveHandler.h"



FinalMoveHandler::FinalMoveHandler(std::shared_ptr<Field> field):Handler(field) {

}


FinalMoveHandler::~FinalMoveHandler()
{
}

void FinalMoveHandler::handle(std::shared_ptr<Request> request)
{
	std::shared_ptr<MoveCommand> command(new MoveCommand(field));
	command->execute(request);
}
