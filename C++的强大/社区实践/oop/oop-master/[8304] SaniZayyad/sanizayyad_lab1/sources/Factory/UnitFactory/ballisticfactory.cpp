#include "ballisticfactory.hpp"

std::shared_ptr<Unit> BallisticFactory::createUnit(const Position2D& position,
                                                 std::shared_ptr<Mediator> mediator)
{
    std::shared_ptr<Unit> unit(new Ballistic(position,mediator));

    return unit;
}
