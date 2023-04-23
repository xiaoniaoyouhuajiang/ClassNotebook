#ifndef KAMIKADZEFACTORY_H
#define KAMIKADZEFACTORY_H

#include "unitfactory.h"

#include "Unit/FlyingUnit/kamikadze.h"


namespace unit {
class KamikadzeFactory : public UnitFactory
{
public:
    virtual std::shared_ptr<Unit>
    createUnit(const Point2D& point,
               std::shared_ptr<Mediator> mediator) const override;
};
}

#endif // KAMIKADZEFACTORY_H
