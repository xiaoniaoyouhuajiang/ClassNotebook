#include "LargeMedicine.h"



LargeMedicine::LargeMedicine()
{
	affectBehavior = std::shared_ptr<AffectBehavior>(new LargeMedicineAffectBehavior());
}


LargeMedicine::~LargeMedicine()
{
}


std::string LargeMedicine::getPath() {
    return "largeMedicine.png";
}
