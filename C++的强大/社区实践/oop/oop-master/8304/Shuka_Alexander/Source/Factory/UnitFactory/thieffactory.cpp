#include "thieffactory.h"

using namespace unit;


std::shared_ptr<Unit>
ThiefFactory::createUnit(const Point2D& point,
                         std::shared_ptr<Mediator> mediator) const
{
    return std::make_shared<Thief>(point, mediator);
}
