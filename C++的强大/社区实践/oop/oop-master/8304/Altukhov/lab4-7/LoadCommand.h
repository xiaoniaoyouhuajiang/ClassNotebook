#pragma once
#include "ICommand.h"
#include <string>
class LoadCommand :
	public ICommand
{
	Base* otherBase;
public:
	LoadCommand(Base*& myBase, Base*& otherBase, std::string& arg);
	void execute();
	int specExecute();
};

