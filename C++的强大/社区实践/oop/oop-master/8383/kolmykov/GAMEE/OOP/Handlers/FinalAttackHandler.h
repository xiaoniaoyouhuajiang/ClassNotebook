#pragma once
#include "Handler.h"
#include "AttackCommand.h"
class FinalAttackHandler :
	public Handler
{
public:
	FinalAttackHandler(std::shared_ptr<Field> field);
	~FinalAttackHandler();
	void handle(std::shared_ptr<Request> request);
};

