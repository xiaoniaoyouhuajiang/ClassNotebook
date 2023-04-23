#pragma once
#include "Handler.h"
class FreeCellForUnitHandler :
	public Handler
{
public:
	FreeCellForUnitHandler(std::shared_ptr<Field> field);
	~FreeCellForUnitHandler();
	void handle(std::shared_ptr<Request> request);
};

