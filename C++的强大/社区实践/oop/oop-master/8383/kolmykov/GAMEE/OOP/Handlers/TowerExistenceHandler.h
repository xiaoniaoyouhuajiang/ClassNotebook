#pragma once
#include "Handler.h"
class TowerExistenceHandler :
	public Handler
{
public:
	TowerExistenceHandler(std::shared_ptr<Field> field);
	~TowerExistenceHandler();
	virtual void handle(std::shared_ptr<Request> request);
};

