#pragma once
#include "ICommand.h"
class AttackCommand : public ICommand {
public:
	AttackCommand(Base*& myBase, int arg1, int arg2); 
	virtual void execute();
};

