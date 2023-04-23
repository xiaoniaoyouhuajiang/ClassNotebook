#include "dragon.h"

using namespace unit;


Dragon::Dragon(const Point2D& point, std::shared_ptr<Mediator> mediator) :
    FlyingUnit(point, mediator)
{
    healthPoints = 100;
}


Dragon::Dragon(const Dragon& unit) : FlyingUnit(unit)
{
    this->doCopy(unit);
}


Dragon& Dragon::operator=(const Dragon& unit)
{
    if (this == &unit) {
        return *this;
    }

    this->doCopy(unit);

    return *this;
}


std::shared_ptr<Unit> Dragon::clone()
{
    return std::make_shared<Dragon>(*this);
}


char Dragon::draw() const
{
    return 'D';
}


size_t Dragon::farm() const
{
    return NO_GOLD;
}
