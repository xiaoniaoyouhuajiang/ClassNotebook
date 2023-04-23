#include "swordmanfactory.hpp"

std::shared_ptr<Unit> SwordManFactory::createUnit(const Position2D& position,
                                                 std::shared_ptr<Mediator> mediator)
{
    std::shared_ptr<Unit> unit(new SwordMan(position,mediator));

    return unit;
}

