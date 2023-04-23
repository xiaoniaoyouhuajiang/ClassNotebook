#include "RemoveCheckTail.h"

addAndRemoveResult RemoveUnitsCheck::check(Field& fld, int x, int y)
{
	if (fld[x][y].unit == nullptr)
		return addAndRemoveResult::removeErrorNoUnit;

	return addAndRemoveResult::unitRemoved;
}

RemoveCoordCheck::RemoveCoordCheck()
{
	next = std::make_shared<RemoveUnitsCheck>();
}

addAndRemoveResult RemoveCoordCheck::check(Field& fld, int x, int y)
{
	size_t fldWidth = fld.getWidth();
	size_t fldHeight = fld.getHeight();

	if (x < 0 || y < 0 || x >= fldWidth || y >= fldHeight || (x < 3 && y < 3))
		return addAndRemoveResult::removeErrorIncorrectCoord;

	return next->check(fld, x, y);
}
