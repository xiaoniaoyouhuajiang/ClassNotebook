#include "healthobject.hpp"

using namespace unit;

HealthObject::HealthObject(const HealthObject& object)
{
    if (object.strategyPattern) {
        this->strategyPattern = object.strategyPattern->clone();
    }
}


HealthObject& HealthObject::operator=(const HealthObject& object)
{
    if (this == &object) {
        return *this;
    }

    if (object.strategyPattern) {
        this->strategyPattern = object.strategyPattern->clone();
    }

    return *this;
}


std::shared_ptr<NeutralObject> HealthObject::clone() const
{
    std::unique_ptr<NeutralObject> object(new HealthObject(*this));
    return object;
}


void HealthObject::selectLogic(std::shared_ptr<unit::Unit> unit)
{
//    Q_UNUSED(unit);

    strategyPattern = std::unique_ptr<StrategyPattern>(new HealthUpdateLogic);
}

char HealthObject::draw() const
{
    return '+';
}
