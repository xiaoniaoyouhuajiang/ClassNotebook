#pragma once
#include "ICommand.h"
#include <string>
class SaveCommand :
	public ICommand
{
	Base* otherBase;
public:
	SaveCommand(Base*& myBase, Base*& otherBase, std::string& arg);
	virtual void execute();
};

