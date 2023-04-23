#include "dragonfactory.hpp"

std::shared_ptr<Unit> DragonFactory::createUnit(const Position2D& position,
                                                 std::shared_ptr<Mediator> mediator)
{
    std::shared_ptr<Unit> unit(new Dragon(position,mediator));

    return unit;
}
