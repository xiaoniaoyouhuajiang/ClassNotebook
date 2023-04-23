#pragma once
#include "ICommand.h"
class MoveCommand :public ICommand {

public:
	MoveCommand(Base*& myBase, int arg1, int arg2, int arg3);
	virtual void execute();
};

