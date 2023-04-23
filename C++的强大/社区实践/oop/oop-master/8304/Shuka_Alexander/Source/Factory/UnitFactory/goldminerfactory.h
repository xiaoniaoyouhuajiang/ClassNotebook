#ifndef GOLDMINERFACTORY_H
#define GOLDMINERFACTORY_H

#include "unitfactory.h"

#include "Unit/StandingUnit/goldminer.h"


namespace unit {
class GoldMinerFactory : public UnitFactory
{
public:
    virtual std::shared_ptr<Unit>
    createUnit(const Point2D& point,
               std::shared_ptr<Mediator> mediator) const override;
};
}

#endif // GOLDMINERFACTORY_H
