#include "swordmanfactory.hpp"

using namespace unit;

std::shared_ptr<Unit> SwordManFactory::createUnit(const Position2D& position,
                                                 std::shared_ptr<Mediator> mediator) const
{

    return std::make_shared<SwordMan>(position,mediator);
}

