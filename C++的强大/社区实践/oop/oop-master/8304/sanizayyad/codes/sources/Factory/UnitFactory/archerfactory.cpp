#include "archerfactory.hpp"

using namespace unit;
std::shared_ptr<Unit> ArcherFactory::createUnit(const Position2D& position,
                                                 std::shared_ptr<Mediator> mediator) const
{
     return std::make_shared<Archer>(position,mediator);

}
