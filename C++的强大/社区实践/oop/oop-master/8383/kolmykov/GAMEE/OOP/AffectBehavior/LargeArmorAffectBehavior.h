#pragma once
#include "AffectBehavior.h"
class LargeArmorAffectBehavior :
	public AffectBehavior
{
public:
	LargeArmorAffectBehavior();
	~LargeArmorAffectBehavior();
    void affect(std::shared_ptr<Unit> unit);
};

