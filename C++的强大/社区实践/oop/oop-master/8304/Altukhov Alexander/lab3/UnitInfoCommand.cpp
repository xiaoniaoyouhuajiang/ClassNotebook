#include "UnitInfoCommand.h"

UnitInfoCommand::UnitInfoCommand(Base*& myBase, int arg1) {
	this->myBase = myBase;
	args.push_back(arg1);
}


void UnitInfoCommand::execute() {//args[id]

	if (!myBase->writeUnitInfo(args[0])) {
		std::cout << "Юнита с таким id не существует!\n";
		return;
	}

}