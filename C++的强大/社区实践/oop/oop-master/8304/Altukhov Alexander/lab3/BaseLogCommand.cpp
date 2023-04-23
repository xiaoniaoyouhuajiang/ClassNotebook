#include "BaseLogCommand.h"

BaseLogCommand::BaseLogCommand(Base*& myBase) {
	this->myBase = myBase;
}


void BaseLogCommand::execute() {//args[type, lvl]
	myBase->writeBaseState();
}