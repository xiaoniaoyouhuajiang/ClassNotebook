#ifndef TOWERFACTORY_H
#define TOWERFACTORY_H

#include "unitfactory.h"

#include "Unit/StandingUnit/tower.h"


namespace unit {
class TowerFactory : public UnitFactory
{
public:
    virtual std::shared_ptr<Unit>
    createUnit(const Point2D& point,
               std::shared_ptr<Mediator> mediator) const override;
};
}

#endif // TOWERFACTORY_H
