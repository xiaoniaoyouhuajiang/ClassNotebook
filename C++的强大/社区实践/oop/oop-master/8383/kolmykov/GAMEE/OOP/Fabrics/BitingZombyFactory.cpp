#include "BitingZombyFactory.h"



BitingZombyFactory::BitingZombyFactory()
{
	type = UnitType::BITING_ZOMBY;
    kind = Kind::ZOMBY;
}


BitingZombyFactory::~BitingZombyFactory()
{
}

std::shared_ptr<Unit> BitingZombyFactory::create(int x, int y, int level)
{
	return std::shared_ptr<Unit>(new BitingZomby(x, y, level));
}


std::string BitingZombyFactory::getPath() {
    return "bitingZomby.png";
}
