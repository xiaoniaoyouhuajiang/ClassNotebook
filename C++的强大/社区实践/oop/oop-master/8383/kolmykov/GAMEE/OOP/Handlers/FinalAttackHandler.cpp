#include "FinalAttackHandler.h"



FinalAttackHandler::FinalAttackHandler(std::shared_ptr<Field> field) : Handler(field) {

}


FinalAttackHandler::~FinalAttackHandler()
{
}

void FinalAttackHandler::handle(std::shared_ptr<Request> request) {
	std::shared_ptr<AttackCommand> command(new AttackCommand(field));
	command->execute(request);
}
