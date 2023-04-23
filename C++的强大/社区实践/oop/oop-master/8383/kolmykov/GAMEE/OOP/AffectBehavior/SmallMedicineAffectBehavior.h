#pragma once
#include "AffectBehavior.h"
class SmallMedicineAffectBehavior :
	public AffectBehavior
{
public:
	SmallMedicineAffectBehavior();
	~SmallMedicineAffectBehavior();
    void affect(std::shared_ptr<Unit> unit);
};

