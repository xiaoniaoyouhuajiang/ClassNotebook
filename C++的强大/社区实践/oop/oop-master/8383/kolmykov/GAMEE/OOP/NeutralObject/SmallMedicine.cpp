#include "SmallMedicine.h"



SmallMedicine::SmallMedicine()
{
	affectBehavior = std::shared_ptr<AffectBehavior>(new SmallMedicineAffectBehavior());
}


SmallMedicine::~SmallMedicine()
{
}


std::string SmallMedicine::getPath() {
    return "smallMedicine.png";
}
