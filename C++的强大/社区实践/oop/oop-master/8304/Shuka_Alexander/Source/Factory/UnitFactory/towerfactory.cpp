#include "towerfactory.h"

using namespace unit;


std::shared_ptr<Unit>
TowerFactory::createUnit(const Point2D& point,
                         std::shared_ptr<Mediator> mediator) const
{
    return std::make_shared<Tower>(point, mediator);
}
