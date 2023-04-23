#pragma once
#include "Command.h"
class CreateUnitCommand :
	public Command
{
public:
	CreateUnitCommand(std::shared_ptr<Field> field);
	~CreateUnitCommand();
	void execute(std::shared_ptr<Request> request);
};

