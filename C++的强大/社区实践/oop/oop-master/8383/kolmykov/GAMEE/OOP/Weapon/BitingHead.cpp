#include "BitingHead.h"



BitingHead::BitingHead()
{
	damage = 150;
	range = 1;
}

BitingHead::BitingHead(const BitingHead & other):Weapon(other)
{
}


BitingHead::~BitingHead()
{
}
