#include "SmallArmorObject.h"



SmallArmorObject::SmallArmorObject()
{
	affectBehavior = std::shared_ptr<AffectBehavior>(new SmallArmorAffectBehavior());
}


SmallArmorObject::~SmallArmorObject()
{
}

//void SmallArmorObject::operator+=(Unit& unit)
//{
//	affectOnUnit(std::shared_ptr<Unit>(&unit));
//}

std::string SmallArmorObject::getPath() {
    return "smallArmorObject.png";
}
