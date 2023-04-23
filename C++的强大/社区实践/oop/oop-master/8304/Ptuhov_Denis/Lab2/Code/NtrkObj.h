#pragma once
#include <vector>
#include "NtrlStrategies.h"

struct NtrlObj
{
	virtual std::vector<char> who() = 0;
	virtual NtrlObjEffect get() = 0;
};

struct HillingWaterFall : NtrlObj
{
	std::vector<char> who();
	NtrlObjEffect get();

private:
	HillingStrategy stg;
};


struct Trap : NtrlObj
{
	std::vector<char> who();
	NtrlObjEffect get();

private:
	HillingStrategy stg;
};

struct PowerStatue : NtrlObj
{
	std::vector<char> who();
	NtrlObjEffect get();

private:
	BaffDamageStrategy stg;
};

struct InsightStatue : NtrlObj
{
	std::vector<char> who();
	NtrlObjEffect get();

private:
	BaffRangeStrategy stg;
};
