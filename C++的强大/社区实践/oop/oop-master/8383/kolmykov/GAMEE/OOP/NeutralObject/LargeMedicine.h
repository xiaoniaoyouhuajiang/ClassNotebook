#pragma once
#include "MedicineObject.h"
#include "LargeMedicineAffectBehavior.h"


class LargeMedicine :
	public MedicineObject
{
public:
	LargeMedicine();
	~LargeMedicine();
    std::string getPath();
};

