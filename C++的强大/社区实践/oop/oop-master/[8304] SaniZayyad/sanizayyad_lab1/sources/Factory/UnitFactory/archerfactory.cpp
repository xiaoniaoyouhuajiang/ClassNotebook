#include "archerfactory.hpp"

std::shared_ptr<Unit> ArcherFactory::createUnit(const Position2D& position,
                                                 std::shared_ptr<Mediator> mediator)
{
    std::shared_ptr<Unit> unit(new Archer(position,mediator));

    return unit;
}
