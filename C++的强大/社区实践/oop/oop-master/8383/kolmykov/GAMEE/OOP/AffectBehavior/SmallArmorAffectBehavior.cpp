#include "SmallArmorAffectBehavior.h"



SmallArmorAffectBehavior::SmallArmorAffectBehavior()
{

}


SmallArmorAffectBehavior::~SmallArmorAffectBehavior()
{
}



void SmallArmorAffectBehavior::affect(std::shared_ptr<Unit> unit)
{
	unit->addArmor(10);
}
