#include "FinalSetTowerHandler.h"



FinalSetTowerHandler::FinalSetTowerHandler(std::shared_ptr<Field> field):Handler(field) {

}


FinalSetTowerHandler::~FinalSetTowerHandler()
{
}

void FinalSetTowerHandler::handle(std::shared_ptr<Request> request) {
	std::shared_ptr<SetTowerCommand> command(new SetTowerCommand(field));
	command->execute(request);
}
