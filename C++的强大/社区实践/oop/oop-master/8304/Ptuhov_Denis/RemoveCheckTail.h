#pragma once
#include "Resourses.h"
#include "Field.h"

struct RemoveCheckTail
{
	virtual addAndRemoveResult check(Field& fld, int x, int y) = 0;
};

struct RemoveUnitsCheck : RemoveCheckTail
{
	RemoveUnitsCheck() = default;
	addAndRemoveResult check(Field& fld, int x, int y);
};

struct RemoveCoordCheck : RemoveCheckTail
{
	RemoveCoordCheck();
	addAndRemoveResult check(Field& fld, int x, int y);

private:
	std::shared_ptr<RemoveCheckTail> next;
};