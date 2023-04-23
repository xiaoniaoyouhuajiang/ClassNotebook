#pragma once
#include "Handler.h"
class FreeCellForTowerHandler :
	public Handler
{
public:
	FreeCellForTowerHandler(std::shared_ptr<Field> field);
	~FreeCellForTowerHandler();
	void handle(std::shared_ptr<Request> request);
};

