#include "CheckTail.h"

AddCoordCheck::AddCoordCheck()
{
	next = std::make_shared<AddUnitsCheck>();
}

addAndRemoveResult AddCoordCheck::check(Field& fld, int x, int y)
{
	size_t fldWidth = fld.getWidth();
	size_t fldHeight = fld.getHeight();

	if (x < 0 || y < 0 || x >= fldWidth || y >= fldHeight || (x < 3 && y < 3))
		return addAndRemoveResult::addErrorIncorrectCoord;

	return next->check(fld, x, y);
}

addAndRemoveResult AddUnitsCheck::check(Field& fld, int x, int y)
{
	if (fld[x][y].unit != nullptr)
		return addAndRemoveResult::addErrorColission;

	return addAndRemoveResult::unitAdded;
}
