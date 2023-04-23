#include "FinalCreateUnitHandler.h"



FinalCreateUnitHandler::FinalCreateUnitHandler(std::shared_ptr<Field> field):Handler(field) {

}


FinalCreateUnitHandler::~FinalCreateUnitHandler()
{
}

void FinalCreateUnitHandler::handle(std::shared_ptr<Request> request) {
	std::shared_ptr<CreateUnitCommand> command(new CreateUnitCommand(field));
	command->execute(request);
}
