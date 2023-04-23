#include "CreateCommand.h"

enum class UnitTypes;

CreateCommand::CreateCommand(Base*& myBase, int arg1, int arg2) {
	this->myBase = myBase;
	args.push_back(arg1);
	args.push_back(arg2);
}


void CreateCommand::execute() {//args[type, lvl]
	if (args[0] > 2 || args[1] < 1 || args[1] > 2) {
		std::cout << "Неправильно указан тип юнита или уровень\n";
		return;
	}
	std::cout << "Создается юнит типа " << args[0] << " уровня " << args[1] << ".\n";
	myBase->createAndSetUnit(static_cast<UnitTypes>(args[0]), args[1]);
	myBase->getParentField()->visualizeField();
}