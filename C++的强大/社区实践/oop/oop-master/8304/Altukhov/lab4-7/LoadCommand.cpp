#include "LoadCommand.h"
#include <string>
LoadCommand::LoadCommand(Base*& myBase, Base*& otherBase, std::string& arg) {
	this->myBase = myBase;
	this->otherBase = otherBase;
	stringArgs.push_back(arg);
}


void LoadCommand::execute() {
	Memento mem;
	//mem.getInfoFromField(myBase->getParentField());
	//mem.getInfoFromBase(myBase, true);
	//mem.getInfoFromBase(otherBase);
	if (mem.loadFromFile(myBase->getParentField(), myBase, otherBase, stringArgs[0])) {
		log << (std::string)"Загрузка выполнена!\n";
	}
	else {
		log << (std::string)"Ошибка при загрузке!\n";
	}
	

}

int LoadCommand::specExecute() {
	Memento mem;
	//mem.getInfoFromField(myBase->getParentField());
	//mem.getInfoFromBase(myBase, true);
	//mem.getInfoFromBase(otherBase);

	if (mem.loadFromFile(myBase->getParentField(), myBase, otherBase, stringArgs[0])) {
		log << (std::string)"Загрузка выполнена!\n";
	}
	else {
		log << (std::string)"Ошибка при загрузке!\n";
	}
	return mem.whatPlayerTurn;
}