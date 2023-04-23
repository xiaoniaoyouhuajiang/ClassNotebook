#pragma once
#include "MoveBehavior.h"
class CarMove :
	public MoveBehavior
{
public:
	CarMove();
	~CarMove();
	virtual void move(std::shared_ptr<Unit> unit) override;
};

