#include "Landscapes.h"

Landscapes Swamp::getLandscapeType()
{
	return this->lendScapeType;
}

bool Swamp::canGo()
{
	return false;
}

Landscapes Plain::getLandscapeType()
{
	return this->lendScapeType;
}

bool Plain::canGo()
{
	return true;
}

Landscapes Hills::getLandscapeType()
{
	return this->lendScapeType;
}

bool Hills::canGo()
{
	return true;
}

LandscapeProxy::LandscapeProxy(Landscapes landscapeType)
{
	landscape = LandscapeFabric::getNewLandscape(landscapeType);
}

Landscapes LandscapeProxy::getLandscapeType()
{
	return landscape->getLandscapeType();
}

bool LandscapeProxy::canGo()
{
	return landscape->canGo();
}


void LandscapeProxy::landscapeInfluence(IUnit* unit)
{
	if (landscape->getLandscapeType() == Landscapes::HILLS) {
		unit->downArmour(5);
	}
	else if (landscape->getLandscapeType() == Landscapes::PLAIN) {
		unit->upHP(3);
	}
}

ILandscape* LandscapeFabric::getNewLandscape(Landscapes type)
{
	if (type == Landscapes::HILLS) return new Hills();
	if (type == Landscapes::SWAMP) return new Swamp();
	if (type == Landscapes::PLAIN) return new Plain();
	return new Plain();
}
