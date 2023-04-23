#include "MediumArmor.h"



MediumArmor::MediumArmor()
{
	defend = 30;
}

MediumArmor::MediumArmor(const MediumArmor & other):Armor(other)
{
}


MediumArmor::~MediumArmor()
{
}
