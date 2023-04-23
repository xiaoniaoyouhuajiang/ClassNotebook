#include "LargeArmorAffectBehavior.h"



LargeArmorAffectBehavior::LargeArmorAffectBehavior()
{
}


LargeArmorAffectBehavior::~LargeArmorAffectBehavior()
{
}

void LargeArmorAffectBehavior::affect(std::shared_ptr<Unit> unit)
{
	unit->addArmor(30);
}
