#pragma once
#include "ICommand.h"
class CreateCommand : public ICommand {

public:
	CreateCommand(Base*& myBase, int arg1, int arg2);
	virtual void execute();

};

