#include "spikeslandscape.h"
#include <qglobal.h>

using namespace unit;


void SpikesLandscape::hurtUnit(std::shared_ptr<Unit> unit) const
{
    if (unit) {
        unit->toHurt(10);
    }
}


bool SpikesLandscape::canMove(std::shared_ptr<Unit> unit) const
{
    Q_UNUSED(unit);
    return true;
}


std::shared_ptr<Landscape> SpikesLandscape::clone() const
{
    return std::make_shared<SpikesLandscape>();
}


char SpikesLandscape::draw() const
{
    return 'x';
}
