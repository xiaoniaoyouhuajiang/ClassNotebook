#include "goldminerfactory.h"

using namespace unit;


std::shared_ptr<Unit>
GoldMinerFactory::createUnit(const Point2D& point,
                             std::shared_ptr<Mediator> mediator) const
{
    return std::make_shared<GoldMiner>(point, mediator);
}
