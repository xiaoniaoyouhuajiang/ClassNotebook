#include "MoveCommand.h"

MoveCommand::MoveCommand(Base*& myBase, int arg1, int arg2, int arg3) {
	this->myBase = myBase;
	args.push_back(arg1);
	args.push_back(arg2);
	args.push_back(arg3);
}


void MoveCommand::execute() {//args[id, x, y]

	if (!myBase->getUnit(args[0])) {
		//std::cout << "Юнита с таким id не существует\n";
		log << (std::string)"Юнита с таким id не существует!\n";
		return;
	}
	if (myBase->getUnit(args[0])->getMoved()) {
		log << (std::string)"Юнит уже ходил в этом ходу!\n";
		return;
	}
	//std::cout << "Юнит " << args[0] << " передвигается по координатам " << args[1] << ", " << args[2] << ".\n";
	log << ("Юнит " + std::to_string(args[0]) + " передвигается по координатам " + std::to_string(args[1]) + ", " + std::to_string(args[2]) + ".\n");
	myBase->getUnit(args[0])->doMove(args[2], args[1]); //из-за всеобщей кривизны y оказался x, a x - y
	myBase->getParentField()->visualizeField();
}