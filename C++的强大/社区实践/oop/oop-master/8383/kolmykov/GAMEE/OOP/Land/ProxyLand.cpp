#include "ProxyLand.h"
#include "Unit.h"


ProxyLand::ProxyLand(std::shared_ptr<Land> land)
{
	this->land = land;
}


ProxyLand::~ProxyLand()
{
}

void ProxyLand::bufUnit(std::shared_ptr<Unit> unit) {
	land->bufUnit(unit);
}
