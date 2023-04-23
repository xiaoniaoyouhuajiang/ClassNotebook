#ifndef DRAGONFACTORY_H
#define DRAGONFACTORY_H

#include "unitfactory.h"

#include "Unit/FlyingUnit/dragon.h"


namespace unit {
class DragonFactory : public UnitFactory
{
public:
    virtual std::shared_ptr<Unit>
    createUnit(const Point2D& point,
               std::shared_ptr<Mediator> mediator) const override;
};
}

#endif // DRAGONFACTORY_H
