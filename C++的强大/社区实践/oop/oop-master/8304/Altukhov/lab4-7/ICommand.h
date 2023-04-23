#pragma once
#include <vector>
#include "Base.h"
#include "Field.h"
#include <iostream>
#include "ProxyLog.h"
class Base;
class Field;
class ICommand {
protected:
	ProxyLog* log;
	Base* myBase;
	Field* myField;
	std::vector<int> args;
	std::vector<std::string> stringArgs;
public:
	
	virtual void execute() = 0;
	void addLog(ProxyLog* log);
};

