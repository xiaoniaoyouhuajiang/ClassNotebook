#pragma once
#include "MedicineObject.h"
#include "SmallMedicineAffectBehavior.h"


class SmallMedicine :
	public MedicineObject
{
public:
	SmallMedicine();
	~SmallMedicine();
    std::string getPath();
};

