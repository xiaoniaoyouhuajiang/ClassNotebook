#pragma once
#include "Handler.h"
#include "MoveCommand.h"


class FinalMoveHandler :
	public Handler
{
public:
	FinalMoveHandler(std::shared_ptr<Field> field);
	~FinalMoveHandler();
	void handle(std::shared_ptr<Request> request);
};

