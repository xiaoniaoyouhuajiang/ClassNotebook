#include "shape.h"

ostream &operator << (ostream &ost, Shape& Object)
{
	Object.print(ost);
	return ost;
}

bool operator== (const Shape& p1, const Shape& p2)
{
	if (p1.leftTopPoint == p2.leftTopPoint &&  p1.mainPointToMove == p2.mainPointToMove)
	{
		return true;
	}
	else
	{
		return false;
	}
}