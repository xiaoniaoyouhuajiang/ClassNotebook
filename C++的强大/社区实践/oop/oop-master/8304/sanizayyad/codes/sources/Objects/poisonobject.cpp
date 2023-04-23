#include "poisonobject.hpp"

using namespace unit;
PoisonObject::PoisonObject(const PoisonObject& object)
{
    if (object.strategyPattern) {
        this->strategyPattern = object.strategyPattern->clone();
    }
}


PoisonObject& PoisonObject::operator=(const PoisonObject& object)
{
    if (this == &object) {
        return *this;
    }

    if (object.strategyPattern) {
        this->strategyPattern = object.strategyPattern->clone();
    }

    return *this;
}


std::shared_ptr<NeutralObject> PoisonObject::clone() const
{
    std::unique_ptr<NeutralObject> object(new PoisonObject(*this));
    return object;
}


void PoisonObject::selectLogic(std::shared_ptr<unit::Unit> unit)
{
//    Q_UNUSED(unit);

    strategyPattern = std::unique_ptr<StrategyPattern>(new PoisonLogic);
}

char PoisonObject::draw() const
{
    return '!';
}
