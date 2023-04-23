#include "desert.hpp"
using namespace unit;
void DesertLandscape::hurtUnit(std::shared_ptr<unit::Unit> unit) const
{
    if (unit) {
           unit->makeDamage(10);
       }
}


bool DesertLandscape::canMove(std::shared_ptr<unit::Unit> unit) const
{
//    not used
    return true;
}


std::shared_ptr<Landscape> DesertLandscape::clone() const
{
    std::shared_ptr<Landscape> landscape(new DesertLandscape);
    return landscape;
}


char DesertLandscape::draw() const
{
    return '*';
}
