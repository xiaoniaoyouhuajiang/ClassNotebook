#pragma once
#include "ICommand.h"
class BaseLogCommand : public ICommand {

public:
	BaseLogCommand(Base*& myBase);
	virtual void execute();
};

