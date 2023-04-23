#pragma once
#include "MoveBehavior.h"
class CommonMove :
	public MoveBehavior
{
public:
	CommonMove();
	~CommonMove();
	void move(std::shared_ptr<Unit> unit)override;
};

