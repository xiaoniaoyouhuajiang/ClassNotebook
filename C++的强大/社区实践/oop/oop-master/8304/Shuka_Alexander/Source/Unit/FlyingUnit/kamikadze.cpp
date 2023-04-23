#include "kamikadze.h"

using namespace unit;


Kamikadze::Kamikadze(const Point2D& point, std::shared_ptr<Mediator> mediator) :
    FlyingUnit(point, mediator)
{
    healthPoints = 70;
}


Kamikadze::Kamikadze(const Kamikadze& unit) : FlyingUnit(unit)
{
    this->doCopy(unit);
}


Kamikadze& Kamikadze::operator=(const Kamikadze& unit)
{
    if (this == &unit) {
        return *this;
    }

    this->doCopy(unit);

    return *this;
}


size_t Kamikadze::farm() const
{
    return NO_GOLD;
}


std::shared_ptr<Unit> Kamikadze::clone()
{
    return std::make_shared<Kamikadze>(*this);
}


char Kamikadze::draw() const
{
    return 'K';
}
