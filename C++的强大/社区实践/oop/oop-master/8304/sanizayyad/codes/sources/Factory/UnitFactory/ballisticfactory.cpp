#include "ballisticfactory.hpp"

using namespace unit;
std::shared_ptr<Unit> BallisticFactory::createUnit(const Position2D& position,
                                                 std::shared_ptr<Mediator> mediator) const
{
    return std::make_shared<Ballistic>(position,mediator);

}
