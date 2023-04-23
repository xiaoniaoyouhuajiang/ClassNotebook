#pragma once
#include "Handler.h"
class TowerPosibilityHandler :
	public Handler
{
public:
	TowerPosibilityHandler(std::shared_ptr<Field> field);
	~TowerPosibilityHandler();
	void handle(std::shared_ptr<Request> request);
};

