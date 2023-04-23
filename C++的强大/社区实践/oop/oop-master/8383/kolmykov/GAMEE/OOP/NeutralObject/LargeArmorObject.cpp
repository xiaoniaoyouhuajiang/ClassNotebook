#include "LargeArmorObject.h"



LargeArmorObject::LargeArmorObject()
{
	affectBehavior = std::shared_ptr<AffectBehavior>(new LargeArmorAffectBehavior());
}


LargeArmorObject::~LargeArmorObject()
{
}

std::string LargeArmorObject::getPath() {
    return "largeArmorObject.png";
}
