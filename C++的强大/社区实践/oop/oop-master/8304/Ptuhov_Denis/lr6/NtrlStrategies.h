#pragma once
#include "Resourses.h"

struct Strategy
{
	virtual NtrlObjEffect effect(int n) = 0;
};

struct HillingStrategy : Strategy
{
	NtrlObjEffect effect(int n);
};

struct BaffDamageStrategy : Strategy
{
	NtrlObjEffect effect(int n);
};

struct BaffRangeStrategy : Strategy
{
	NtrlObjEffect effect(int n);
};

