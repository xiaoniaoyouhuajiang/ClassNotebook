#pragma once
#include "Command.h"
class AttackCommand :
	public Command
{
public:
	AttackCommand(std::shared_ptr<Field> field);
	~AttackCommand();
	void execute(std::shared_ptr<Request> request);
};

