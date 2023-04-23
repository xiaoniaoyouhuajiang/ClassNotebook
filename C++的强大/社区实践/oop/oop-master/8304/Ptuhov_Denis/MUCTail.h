#pragma once
#include "Resourses.h"
#include "Field.h"

struct MUCTail
{
	virtual BaseMUCResult check(Field& fld, int n) = 0;
};

struct BiggerCheck : MUCTail
{
	BaseMUCResult check(Field& fld, int n);
};

struct PositivelyCheck : MUCTail
{
	PositivelyCheck();

	BaseMUCResult check(Field& fld, int n);

private:
	std::shared_ptr<MUCTail> next;
};
