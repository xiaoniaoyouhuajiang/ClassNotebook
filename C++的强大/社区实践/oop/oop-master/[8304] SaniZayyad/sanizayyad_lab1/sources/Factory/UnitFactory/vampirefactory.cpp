#include "vampirefactory.hpp"

std::shared_ptr<Unit> VampireFactory::createUnit(const Position2D& position,
                                                 std::shared_ptr<Mediator> mediator)
{
    std::shared_ptr<Unit> unit(new Vampire(position,mediator));

    return unit;
}
