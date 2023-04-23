#include "foglandscape.h"
#include <qglobal.h>

using namespace unit;


void FogLandscape::hurtUnit(std::shared_ptr<Unit> unit) const
{
    Q_UNUSED(unit);
}


bool FogLandscape::canMove(std::shared_ptr<Unit> unit) const
{
    Q_UNUSED(unit);
    return false;
}


std::shared_ptr<Landscape> FogLandscape::clone() const
{
    std::shared_ptr<Landscape> landscape(new FogLandscape);
    return landscape;
}


char FogLandscape::draw() const
{
    return '*';
}
