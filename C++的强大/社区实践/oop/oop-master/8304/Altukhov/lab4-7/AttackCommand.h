#pragma once
#include "ICommand.h"
class AttackCommand : public ICommand {
private:
	Base* enemyBase;
public:
	AttackCommand(Base*& myBase, Base*& enemyBase, int arg1, int arg2);
	virtual void execute();
};

