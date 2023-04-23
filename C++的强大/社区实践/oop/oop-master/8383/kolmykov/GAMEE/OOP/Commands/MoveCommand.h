#pragma once
#include "Command.h"
class MoveCommand :
	public Command
{
public:
	MoveCommand(std::shared_ptr<Field> field);
	~MoveCommand();
	void execute(std::shared_ptr<Request> request);
};

