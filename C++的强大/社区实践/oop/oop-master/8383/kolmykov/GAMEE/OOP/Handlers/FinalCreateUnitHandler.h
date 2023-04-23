#pragma once
#include "Handler.h"
#include "CreateUnitCommand.h"
class FinalCreateUnitHandler :
	public Handler
{
public:
	FinalCreateUnitHandler(std::shared_ptr<Field> field);
	~FinalCreateUnitHandler();
	void handle(std::shared_ptr<Request> request);
};

