#include "LiteArmor.h"



LiteArmor::LiteArmor() 
{
	defend = 10;
}

LiteArmor::LiteArmor(const LiteArmor & other):Armor(other)
{
}


LiteArmor::~LiteArmor()
{
}
