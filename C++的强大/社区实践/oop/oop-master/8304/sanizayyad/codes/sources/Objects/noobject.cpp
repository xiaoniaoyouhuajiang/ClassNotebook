#include "noobject.hpp"

using namespace unit;

NoObject::NoObject(const NoObject& object)
{
    if (object.strategyPattern) {
        this->strategyPattern = object.strategyPattern->clone();
    }
}


NoObject& NoObject::operator=(const NoObject& object)
{
    if (this == &object) {
        return *this;
    }

    if (object.strategyPattern) {
        this->strategyPattern = object.strategyPattern->clone();
    }

    return *this;
}


std::shared_ptr<NeutralObject> NoObject::clone() const
{
    std::unique_ptr<NeutralObject> object(new NoObject(*this));
    return object;

}


void NoObject::selectLogic(std::shared_ptr<unit::Unit> unit)
{
//    Q_UNUSED(unit);

    strategyPattern = std::unique_ptr<NoLogic>(new NoLogic);
}


char NoObject::draw() const
{
    return '.';
}
