#include "kamikadzefactory.h"

using namespace unit;


std::shared_ptr<Unit>
KamikadzeFactory::createUnit(const Point2D& point,
                             std::shared_ptr<Mediator> mediator) const
{
    return std::make_shared<Kamikadze>(point, mediator);
}
