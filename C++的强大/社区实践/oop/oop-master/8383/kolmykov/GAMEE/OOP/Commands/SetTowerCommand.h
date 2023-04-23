#pragma once
#include "Command.h"
class SetTowerCommand :
	public Command
{
public:
	SetTowerCommand(std::shared_ptr<Field> field);
	~SetTowerCommand();
	void execute(std::shared_ptr<Request> request);
};

