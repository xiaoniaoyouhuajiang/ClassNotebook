#include "spearmanfactory.hpp"

std::shared_ptr<Unit> SpearManFactory::createUnit(const Position2D& position,
                                                 std::shared_ptr<Mediator> mediator)
{
    std::shared_ptr<Unit> unit(new SpearMan(position,mediator));

    return unit;
}
