#include "MoveCommand.h"

MoveCommand::MoveCommand(Base*& myBase, int arg1, int arg2, int arg3) {
	this->myBase = myBase;
	args.push_back(arg1);
	args.push_back(arg2);
	args.push_back(arg3);
}


void MoveCommand::execute() {//args[id, x, y]

	if (!myBase->getUnit(args[0])) {
		std::cout << "Юнита с таким id не существует\n";
		return;
	}
	std::cout << "Юнит " << args[0] << " передвигается по координатам " << args[1] << ", " << args[2] << ".\n";
	myBase->getUnit(args[0])->doMove(args[1], args[2]);
	myBase->getParentField()->visualizeField();
}