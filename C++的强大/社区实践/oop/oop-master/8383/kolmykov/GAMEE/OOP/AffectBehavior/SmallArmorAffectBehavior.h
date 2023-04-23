#pragma once
#include "AffectBehavior.h"
class SmallArmorAffectBehavior :
	public AffectBehavior
{
public:
	SmallArmorAffectBehavior();
	~SmallArmorAffectBehavior();
	void affect(std::shared_ptr<Unit> unit);
};

