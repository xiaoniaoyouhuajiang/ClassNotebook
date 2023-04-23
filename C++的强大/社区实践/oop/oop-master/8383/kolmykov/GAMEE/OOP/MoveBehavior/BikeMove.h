#pragma once
#include "MoveBehavior.h"
class BikeMove :
	public MoveBehavior
{
public:
	BikeMove();
	~BikeMove();
	virtual void move(std::shared_ptr<Unit> unit) override;
};

