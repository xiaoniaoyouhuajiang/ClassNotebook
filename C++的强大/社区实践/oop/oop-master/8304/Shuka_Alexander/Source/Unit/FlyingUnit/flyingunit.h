#ifndef FLYINGUNIT_H
#define FLYINGUNIT_H

#include "Unit/unit.h"


namespace unit {
class FlyingUnit : public Unit,
        public std::enable_shared_from_this<Unit>
{
public:
    explicit FlyingUnit(const Point2D& point,
                        std::shared_ptr<Mediator> mediator);

    FlyingUnit(const FlyingUnit& unit);

    virtual bool moveLeft() override;
    virtual bool moveRight() override;
    virtual bool moveTop() override;
    virtual bool moveBottom() override;

    virtual bool isFly() const override;
};
}

#endif // FLYINGUNIT_H
