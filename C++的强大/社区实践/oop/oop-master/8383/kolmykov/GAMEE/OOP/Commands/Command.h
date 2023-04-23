#pragma once
#include "Request.h"
#include "Field.h"
class Command
{
protected:
	std::shared_ptr<Field> field;
public:
	Command(std::shared_ptr<Field> field);
	~Command();
	virtual void execute(std::shared_ptr<Request> request);
};

