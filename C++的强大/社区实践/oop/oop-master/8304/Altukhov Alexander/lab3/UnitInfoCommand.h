#pragma once
#include "ICommand.h"
class UnitInfoCommand : public ICommand {

public:
	UnitInfoCommand(Base*& myBase, int arg1);//id
	virtual void execute();
};

