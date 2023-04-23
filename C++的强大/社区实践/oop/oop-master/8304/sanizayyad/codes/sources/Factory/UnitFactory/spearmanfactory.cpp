#include "spearmanfactory.hpp"

using namespace unit;
std::shared_ptr<Unit> SpearManFactory::createUnit(const Position2D& position,
                                                 std::shared_ptr<Mediator> mediator) const
{
     return std::make_shared<SpearMan>(position,mediator);

}
