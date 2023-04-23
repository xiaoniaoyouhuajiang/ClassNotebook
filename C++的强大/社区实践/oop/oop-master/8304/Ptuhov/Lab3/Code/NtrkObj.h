#pragma once
#include <vector>
#include "NtrlStrategies.h"

struct NtrlObj
{
	virtual std::vector<char> who() = 0;
	virtual NtrlObjEffect get() = 0;
};

struct NtrlObjNameExpansion : NtrlObj
{
	virtual char getName();
	char name;
};

struct HillingWaterFall : NtrlObjNameExpansion
{
	HillingWaterFall();

	std::vector<char> who();
	NtrlObjEffect get();

private:
	HillingStrategy stg;
};


struct Trap : NtrlObjNameExpansion
{
	Trap();

	std::vector<char> who();
	NtrlObjEffect get();

private:
	HillingStrategy stg;
};

struct PowerStatue : NtrlObjNameExpansion
{
	PowerStatue();

	std::vector<char> who();
	NtrlObjEffect get();

private:
	BaffDamageStrategy stg;
};

struct InsightStatue : NtrlObjNameExpansion
{
	InsightStatue();

	std::vector<char> who();
	NtrlObjEffect get();

private:
	BaffRangeStrategy stg;
};
