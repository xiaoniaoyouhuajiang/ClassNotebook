#pragma once
#include "UnitTier1.h"
#include "UnitTier2.h"
#include "UnitTier3.h"
#include <memory>


struct UnitFactory
{
	virtual std::shared_ptr<UnitBase> createType1() = 0;
	virtual std::shared_ptr<UnitBase> createType2() = 0;
};

struct Tier1Factory : UnitFactory
{
	Tier1Factory() = default;

	std::shared_ptr<UnitBase> createType1();
	std::shared_ptr<UnitBase> createType2();
};

struct Tier2Factory : UnitFactory
{
	Tier2Factory() = default;

	std::shared_ptr<UnitBase> createType1();
	std::shared_ptr<UnitBase> createType2();
};

struct Tier3Factory : UnitFactory
{
	Tier3Factory() = default;

	std::shared_ptr<UnitBase> createType1();
	std::shared_ptr<UnitBase> createType2();
};