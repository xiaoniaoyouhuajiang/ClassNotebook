#pragma once
#include "MoveBehavior.h"
class FatZombyMoveBehavior :
	public MoveBehavior
{
protected:
	int step;
public:
	FatZombyMoveBehavior();
	~FatZombyMoveBehavior();
	virtual void move(std::shared_ptr<Unit> unit)override;
};

