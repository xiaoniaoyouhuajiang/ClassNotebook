#include "dragonfactory.h"

using namespace unit;


std::shared_ptr<Unit>
DragonFactory::createUnit(const Point2D& point,
                          std::shared_ptr<Mediator> mediator) const
{
    return std::make_shared<Dragon>(point, mediator);
}
