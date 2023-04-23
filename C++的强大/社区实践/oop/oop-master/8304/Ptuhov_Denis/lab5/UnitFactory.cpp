#include "UnitFactory.h"

std::shared_ptr<UnitBase> Tier1Factory::createType1()
{
	return std::make_shared<Mage>();
}

std::shared_ptr<UnitBase> Tier1Factory::createType2()
{
	return std::make_shared<Assasin>();
}

std::shared_ptr<UnitBase> Tier2Factory::createType1()
{
	return std::make_shared<Archer>();
}

std::shared_ptr<UnitBase> Tier2Factory::createType2()
{
	return std::make_shared<Spearman>();
}

std::shared_ptr<UnitBase> Tier3Factory::createType1()
{
	return std::make_shared<Scout>();
}

std::shared_ptr<UnitBase> Tier3Factory::createType2()
{
	return std::make_shared<Warrior>();
}
