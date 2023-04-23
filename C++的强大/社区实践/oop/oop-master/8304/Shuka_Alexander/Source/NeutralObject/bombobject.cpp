#include "bombobject.h"

using namespace unit;


BombObject::BombObject(const BombObject& object)
{
    if (object.strategy) {
        this->strategy = object.strategy->clone();
    }
}


BombObject& BombObject::operator=(const BombObject& object)
{
    if (this == &object) {
        return *this;
    }

    if (object.strategy) {
        this->strategy = object.strategy->clone();
    }

    return *this;
}


std::shared_ptr<NeutralObject> BombObject::clone() const
{
    return std::make_shared<BombObject>(*this);
}


char BombObject::draw() const
{
    return '-';
}


void BombObject::selectStrategy(std::shared_ptr<Unit> unit)
{
    Q_UNUSED(unit);

    strategy = std::make_shared<KillStrategy>();
}
