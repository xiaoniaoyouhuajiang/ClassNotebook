#pragma once
#include "LandInterface.h"
#include "Land.h"
#include <memory>


class ProxyLand :
	public LandInterface
{
private:
	std::shared_ptr<Land> land;
public:
	ProxyLand(std::shared_ptr<Land> land);
	~ProxyLand();
	void bufUnit(std::shared_ptr<Unit> unit);
};

