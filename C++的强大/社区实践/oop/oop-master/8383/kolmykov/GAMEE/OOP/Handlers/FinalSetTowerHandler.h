#pragma once
#include "Handler.h"
#include "SetTowerCommand.h"
class FinalSetTowerHandler :
	public Handler
{
public:
	FinalSetTowerHandler(std::shared_ptr<Field> field);
	~FinalSetTowerHandler();
	void handle(std::shared_ptr<Request> request);
};

