#ifndef THIEFFACTORY_H
#define THIEFFACTORY_H

#include "unitfactory.h"

#include "Unit/GroundUnit/thief.h"


namespace unit {
class ThiefFactory : public UnitFactory
{
public:
    virtual std::shared_ptr<Unit>
    createUnit(const Point2D& point,
               std::shared_ptr<Mediator> mediator) const override;
};
}

#endif // THIEFFACTORY_H
