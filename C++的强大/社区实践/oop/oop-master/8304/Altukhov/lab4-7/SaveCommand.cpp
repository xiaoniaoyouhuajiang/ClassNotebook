#include "SaveCommand.h"
#include <string>
SaveCommand::SaveCommand(Base*& myBase, Base*& otherBase, std::string& arg) {
	this->myBase = myBase;
	this->otherBase = otherBase;
	stringArgs.push_back(arg);
}


void SaveCommand::execute() {

	Memento mem;
	mem.getInfoFromField(myBase->getParentField());
	mem.getInfoFromBase(myBase, true);
	mem.getInfoFromBase(otherBase);
	mem.saveToFile(stringArgs[0]);
	log << (std::string)"Сохранение выполнено!\n";
}