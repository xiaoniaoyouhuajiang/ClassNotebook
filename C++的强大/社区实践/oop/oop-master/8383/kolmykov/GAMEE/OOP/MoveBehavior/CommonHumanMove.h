#pragma once
#include "MoveBehavior.h"

class CommonHumanMove :
	public MoveBehavior
{
public:
	CommonHumanMove();
	~CommonHumanMove();
	void move(std::shared_ptr<Unit> unit)override;
};

