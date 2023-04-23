#pragma once
#include <vector>
#include "Base.h"
#include <iostream>
class Base;
class ICommand {
protected:
	Base* myBase;
	std::vector<int> args;
public:
	virtual void execute() = 0;
};

