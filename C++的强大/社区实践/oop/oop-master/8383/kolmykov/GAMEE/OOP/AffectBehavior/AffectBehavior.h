#pragma once
#include <memory>
#include "Unit.h"
class AffectBehavior
{
public:
	AffectBehavior();
	~AffectBehavior();
	virtual void affect(std::shared_ptr<Unit> unit);
};

