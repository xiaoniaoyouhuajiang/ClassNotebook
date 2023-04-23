#include "dragonfactory.hpp"
using namespace unit;
std::shared_ptr<Unit> DragonFactory::createUnit(const Position2D& position,
                                                 std::shared_ptr<Mediator> mediator) const
{
     return std::make_shared<Dragon>(position,mediator);

}
