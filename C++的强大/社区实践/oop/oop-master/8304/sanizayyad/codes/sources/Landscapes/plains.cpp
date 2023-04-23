#include "plains.hpp"
using namespace unit;

void PlainsLandscape::hurtUnit(std::shared_ptr<unit::Unit> unit) const
{
//    not used
}


bool PlainsLandscape::canMove(std::shared_ptr<unit::Unit> unit) const
{
//    not used
    return true;
}


std::shared_ptr<Landscape> PlainsLandscape::clone() const
{
    std::shared_ptr<Landscape> landscape(new PlainsLandscape);
    return landscape;
}


char PlainsLandscape::draw() const
{
    return '-';
}
