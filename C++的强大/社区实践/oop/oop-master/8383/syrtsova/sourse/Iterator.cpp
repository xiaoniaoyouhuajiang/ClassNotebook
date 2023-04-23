#include "pch.h"
#include "Iterator.h"
#include "Units.h"

void Iterator::setLinksUnit(Units *link, int count)
{
	link_unit[count-1] = link;
	link_unit[count] = NULL;
}


Units* Iterator::getLinkUnit(int pos)
{
	return link_unit[pos - 1];
}

Units** Iterator::getAllUnits()
{
	return link_unit;
}


Iterator::Iterator()
{
	link_unit[0] = NULL;
}
