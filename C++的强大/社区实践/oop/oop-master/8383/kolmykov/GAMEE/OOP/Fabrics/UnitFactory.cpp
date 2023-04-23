#include "UnitFactory.h"



UnitFactory::UnitFactory()
{
}


UnitFactory::~UnitFactory()
{
}


std::shared_ptr<Unit> UnitFactory::create(int x, int y, int level)
{
	return std::shared_ptr<Unit>(nullptr);
}

UnitType UnitFactory::getType()
{
	return type;
}


std::string UnitFactory::getPath() {
    return "";
}


Kind UnitFactory::getKind() {
    return kind;
}
