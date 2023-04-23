#pragma once
#include "Handler.h"
class UnitExistenceHandler :
	public Handler
{
public:
	UnitExistenceHandler(std::shared_ptr<Field> field);
	~UnitExistenceHandler();
	void handle(std::shared_ptr<Request> request);
};

