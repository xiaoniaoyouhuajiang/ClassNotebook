#pragma once
#include "Resourses.h"
#include "Field.h"

struct AddCheckTail
{
	virtual addAndRemoveResult check(Field& fld, int x, int y) = 0;
};

struct AddUnitsCheck : AddCheckTail
{
	AddUnitsCheck() = default;
	addAndRemoveResult check(Field& fld, int x, int y);

};

struct AddCoordCheck : AddCheckTail
{
	AddCoordCheck();
	addAndRemoveResult check(Field& fld, int x, int y);

private:
	std::shared_ptr<AddCheckTail> next;
};