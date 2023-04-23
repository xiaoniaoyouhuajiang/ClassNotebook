#include "proxylandscape.h"

using namespace unit;


ProxyLandscape::ProxyLandscape()
{
    this->landscape = std::make_shared<RoadLandscape>();
}


ProxyLandscape::ProxyLandscape(std::shared_ptr<Landscape> landscape)
{
    this->landscape = landscape;
}


void ProxyLandscape::hurtUnit(std::shared_ptr<Unit> unit) const
{
    if (unit && !unit->isFly()) {
        this->landscape->hurtUnit(unit);
    }
}


bool ProxyLandscape::canMove(std::shared_ptr<Unit> unit) const
{
    if (unit && unit->isFly()) {
        return this->landscape->canMove(unit);
    }

    return true;
}


std::shared_ptr<Landscape> ProxyLandscape::clone() const
{
    return std::make_shared<ProxyLandscape>(this->landscape->clone());
}


char ProxyLandscape::draw() const
{
    return landscape->draw();
}
