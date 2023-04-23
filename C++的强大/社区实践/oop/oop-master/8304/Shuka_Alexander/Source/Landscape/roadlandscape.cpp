#include "roadlandscape.h"
#include <qglobal.h>

using namespace unit;


void RoadLandscape::hurtUnit(std::shared_ptr<Unit> unit) const
{
    Q_UNUSED(unit);
}


bool RoadLandscape::canMove(std::shared_ptr<Unit> unit) const
{
    Q_UNUSED(unit);
    return true;
}


std::shared_ptr<Landscape> RoadLandscape::clone() const
{
    return std::make_shared<RoadLandscape>();
}


char RoadLandscape::draw() const
{
    return '.';
}
