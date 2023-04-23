#ifndef DRAGON_H
#define DRAGON_H

#include "flyingunit.h"


namespace unit {
class Dragon : public FlyingUnit
{
public:
    explicit Dragon(const Point2D& point,
                    std::shared_ptr<Mediator> mediator);

    Dragon(const Dragon& unit);
    Dragon& operator=(const Dragon& unit);

    virtual size_t farm() const override;

    virtual std::shared_ptr<Unit> clone() override;

    virtual char draw() const override;
};
}

#endif // DRAGON_H
