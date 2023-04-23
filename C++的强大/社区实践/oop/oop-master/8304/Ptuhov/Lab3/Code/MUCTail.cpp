#include "MUCTail.h"

PositivelyCheck::PositivelyCheck()
{
	next = std::make_shared<BiggerCheck>();
}

BaseMUCResult PositivelyCheck::check(Field& fld, int n)
{
	if (n < 0)
		return BaseMUCResult::incorrectData;

	return next->check(fld, n);
}

BaseMUCResult BiggerCheck::check(Field& fld, int n)
{
	if (n < fld.getBaseUnitsCnt())
		return BaseMUCResult::alreadyBigger;

	return BaseMUCResult::correct;
}
